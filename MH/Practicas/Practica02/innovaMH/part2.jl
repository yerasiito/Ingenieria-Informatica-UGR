### A Pluto.jl notebook ###
# v0.19.25

using Markdown
using InteractiveUtils

# This Pluto notebook uses @bind for interactivity. When running this notebook outside of Pluto, the following 'mock version' of @bind gives bound variables a default value (instead of an error).
macro bind(def, element)
    quote
        local iv = try Base.loaded_modules[Base.PkgId(Base.UUID("6e696c72-6542-2067-7265-42206c756150"), "AbstractPlutoDingetjes")].Bonds.initial_value catch; b -> missing; end
        local el = $(esc(element))
        global $(esc(def)) = Core.applicable(Base.get, el) ? Base.get(el) : iv(el)
        el
    end
end

# ╔═╡ 3d1cc3c8-dc80-11ed-3163-9d457a2fc8f2
begin
	using Pkg
	Pkg.activate(".")
	using PlutoUI
	import Distances
	using Plots
	using Random: shuffle, seed!
	using PlutoTeachingTools
	using StatsBase: samplepair
	using DataFrames
	using Test
	using Distributions
	using Printf
	using Logging
	verbose = SimpleLogger(Logging.Debug)
	muestra_log(a)=with_logger(a,verbose)
	PlutoTeachingTools.set_language!(PlutoTeachingTools.get_language_from_env())
	PlutoUI.TableOfContents(title="📚 Índice", indent=true)
end

# ╔═╡ f8623f68-7151-4416-9ffe-87d704ce0aff
md"# Resolviendo el TSP con Metaheurísticas, Parte 2: Algoritmos Genéticos"

# ╔═╡ 421c26f4-e9fe-4f53-917f-4ade85d96cc7
md"""
## Sobre este documento

Este documento forma parte del **Proyecto de Innovación Docente Desarrollo de herramientas web interactivas para el aprendizaje de Metaheurísticas** asociado a la asignatura de Metaheurísticas que se imparte para el _Grado en Ingeniería Informática_ (aunque abierta a grados dobles) en la **Universidad de Granada (UGR)**.

En este sistema interactivo se mostrará cómo se puede aplicar un problema concreto, el _Viajante de Comercio_ para resolverlo con distintas metaheurísticas, algo semejante a lo que tienen que hacer los y las estudiantes de la asignatura, pero con problemas distintos. Al igual que las prácticas de la asignatura, este entorno web está dividido en tres partes, cada una de ellas abordando distintas metaheurísticas sobre el mismo problema.
"""

# ╔═╡ ab1e47c3-3dab-4982-a7ec-7fdd196f5d24
md"""
## Instrucciones

Este documento está en formato [Pluto](https://plutojl.org/) para ofrecer un entorno reactivo, lo cual quiere decir que se pueden pulsar botones o cambiar valores usando elementos visuales (como Select, sliders, ...) y el sistema se
actualiza.

El código fuente disponible está en el lenguaje de programación [Julia](https://julialang.org/), que es muy similar a Python. Lo he escogido porque es muy legible, similar al seudocódigo pero al mismo tiempo es ejecutable. Se puede seleccionar *Edit in binder* y se podrá editar en una copia local.

!!! warning

	Aunque Julia es muy similar a Python hay algunas diferencias, comentaré las más notables: 
    - Los vectores se acceden desde la posición 1 hasta tam, en vez de desde la posición 0 hasta tam-1 (siendo tam el  tamaño del vector). 
    - Los rangos se ponen como 1:N, ambos incluídos, y no range(1, N+1) como en Python.
    - Julia ya tiene soporte para vectores y matrices, no es necesario usar una librería como _numpy_ en Python.
	- Dentro de una cadena se puede usar $ para mostrar los valores de una variable (similar al fmt de Python).
	- La instrucción con "." indica que se hace para todos los elementos, por lo que vector1 .= vector2 copia todo el vector, y all(vector1 .== vector2) comprueba que todos los elementos de ambos vectores sean iguales.

	Hay recursos _online_ para ver ciertas [diferencias entre Python y Julia](https://towardsdatascience.com/moving-code-from-python-to-julia-beware-of-false-friends-160573a5d552), pero no es necesario profundizar para entender los algoritmos y "_jugar_", si se quiere, con el código. 
"""

# ╔═╡ ba86256b-134b-4309-88ad-4bf9296c7d42
TwoColumnWideLeft(
md"""
## El problema del Viajante de Comercio

El problema del Viajante de Comercio (_Travelman Salesman Problem_, TSP) es un problema conocido de la literatura, en el que existe un viajante que debe de recorrer una serie de ciudades y desea encontrar la mejor ruta para ello. Por tanto, el problema consiste en:

- Encontrar la ruta más corta entre todas las ciudades.
- Pasar por cada ciudad únicamente una vez.
- Volver a la ciudad origen.

El objetivo es encontrar la asignación $S$ que minimiza:
```math
\displaystyle \sum_{i=0}^{N-1}Distancia({S_i,S_{i+1}}) + Distancia({S_N,S_0})
```
""",RobustLocalResource("https://images.danimolina.net/TSP.jpg", "TSP.jpg"))

# ╔═╡ 903c9853-acdc-4495-855d-3d4ce2242bf3
begin
	function description(fname)
		open(fname) do file
			line = readline(file)
			(attrib, val) = split(line, ":") .|> strip
			
			while (attrib != "COMMENT")
				line = readline(file)
				(attrib, val) = split(line, ":") .|> strip
			end
			return val |> strip
		end
	end
	fnames = filter(endswith("tsp"), readdir("data", join=true))
	md"""
Para abordar el problema usaremos un conjunto de ciudades de TSP sacadas del [TSPlib](http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/)

Escoge un problema: 
$(@bind fname Select([name => description(name) for name in fnames], default=fnames[5]))
"""
end

# ╔═╡ 85e41585-b696-42e7-80d5-0c980a30a536
begin
	begin
	function read_TSP(fname)
		@assert isfile(fname)
	
		open(fname) do file
			line = readline(file)
			N = 0

			while (contains(line, ":"))
				(atrib,val) = split(line, ":") .|> strip
				if atrib == "DIMENSION"
					N = parse(Int, val)
				end
				line = readline(file) |> strip
			end
			@assert line == "NODE_COORD_SECTION"
			local distances = zeros(Float32, N, N)
			local position_cities = Matrix{Float32}(undef, 2, N)
			
			for i in 1:N
				line = readline(file)
				(_, x, y) = split(line, " ", keepempty=false)
				x, y = parse.(Ref(Float32), (x, y))
				position_cities[1,i] = x
				position_cities[2,i] = y
			end
			#posi = transpose(position_cities)
			distances = Distances.pairwise(Distances.Euclidean(), position_cities, dims=2);
			return N, position_cities, distances;
		end
	end
end
	const N, Position_cities, Distances_cities = read_TSP(fname)
	nothing
end

# ╔═╡ 929dbc59-8d47-438c-aa6b-a797cf8cdb73
begin
	function plot_TSP(options=Dict{}())
		global Position_cities
		position_cities = Position_cities
		scatter(position_cities[1,:], position_cities[2,:]; title=description(fname), legend=false, axis=false, options...)
	end
	plot_TSP()
end

# ╔═╡ 04437555-ddb3-49b6-98cc-cf5687af4c08
md"""
# Aplicando Algoritmos Genéticos

Vamos a aplicar Algoritmos Genéticos para resolver el problema. En particular vamos a aplicar un Algoritmo Genético Generacional y un Algoritmo Genético Estacionario.

Los algoritmos genéticos son algoritmos poblacionales, en los que se mantiene no una solución, sino un conjunto de soluciones en memoria, que son combinados para generar nuevas soluciones, de esa manera la población de soluciones va evolucionando hacia mejores soluciones. 

Se basa en la heurística/idea de que combinando soluciones buenas pueden obtenerse soluciones mejores.
"""

# ╔═╡ 08bec682-efa6-4bc0-b739-0ddd02f8f0d8
md"""
## Algoritmo Genético Generacional

El esquema se visualiza a continuación:

Mientras no se cumpla el criterio de parada, es decir, mientras no se haya generado un número máximo de evaluaciones, se aplican sucesivamente las siguientes fases:

$(RobustLocalResource("https://images.danimolina.net/agg.png", "agg.png"))

- Selección: Se seleccionan soluciones de la población original para constituir una población de igual tamaño. Se seleccionan de forma aleatoriamente, pero normalmente con mayor tendencia a escoger las que presenten mayor fitness.

- Cruce: Se cruzan pares de soluciones para crear nuevas soluciones, reemplazando a las originales. Dado que tras la selección las soluciones están desordenadas, se pueden combinar por pares (la 1 con la 2ª, la 3ª con la 4ª, ...). No todas son cruzadas, solo el P\_c % de pares.

- Mutación: Con una cierta probabilidad P_mut muy baja, se mutan las nuevas soluciones, mediante un cambio muy pequeño.

- Reemplazo: Las nuevas soluciones, la nueva población, reemplaza a la población anterior. Para evitar perder la mejor solución anterior, se copia en la nueva si no está.

A continuación vamos a ver la implementación.
"""

# ╔═╡ 6f75ee5e-8b40-42ae-b59f-fc17a2c16800
md"""
## Algoritmo Genético Estacionario

El esquema se visualiza a continuación:

Mientras no se cumpla el criterio de parada, es decir, mientras no se haya generado un número máximo de evaluaciones, se aplican sucesivamente las siguientes fases:

$(RobustLocalResource("https://images.danimolina.net/age.png", "age.png"))

- Selección: Se seleccionan dos soluciones de la población original. Se seleccionan de forma aleatoriamente, pero normalmente con mayor tendencia a escoger las que presenten mayor fitness.

- Cruce: Se cruzan el par de soluciones seleccionadas para crear dos nuevas soluciones, reemplazando a las originales.

- Mutación: Con una cierta probabilidad P_mut muy baja, se mutan las nuevas soluciones, mediante un cambio muy pequeño.

- Reemplazo: Las nuevas soluciones, reemplazan a las dos peores si las mejoran, es elitista por naturaleza.

A continuación vamos a ver la implementación.
"""

# ╔═╡ e07d5db1-fedb-4883-9e7b-42bbeb1196c4
md"""
## Experimentos
"""

# ╔═╡ e8ccadcf-ae4d-4014-a3bc-0d08b1c7fb58
begin
md"""
Vamos a aplicarlo. El Tiempo Real indica que conforme se actualice el control deslizante se ejecuta. Si no se marca se evalúan hasta el máximo de evaluaciones y luego. Es recomendable solo usar el Modo en Tiempo Real en problemas pequeños.

$(@bind ag_number_evals confirm(NumberField(1000:1000:50_000, default=1000)))
$(@bind online MultiCheckBox([\"Modo Tiempo Real\"]))
"""
end

# ╔═╡ 441219bc-c438-4159-ad1e-8441cdd850e9
@bind boton_seed Button("Inicia Semilla")

# ╔═╡ 4e1cf32a-9387-4b6b-b324-d5ecb14e614d
begin 
	boton_seed
	seed_value = rand(DiscreteUniform(0, 3000))
	md"""
Semilla: $(seed_value)
"""
end	

# ╔═╡ abb709a1-7344-4e84-a24f-443caed0fc00
md"""
Evaluaciones AGG: $(@bind global_evals_agg Slider(50:50:ag_number_evals))
"""

# ╔═╡ 1ca679ff-faf5-4194-9da3-3f8811bb3049
md"""
Evaluaciones AGE: $(@bind global_evals_age Slider(50:50:ag_number_evals))
"""

# ╔═╡ ddb0cea0-dfd7-40a7-a6c3-8dbb68c042d3
if isempty(online)
md"""
Evaluaciones AGG y AGE: $(@bind global_evals_ag Slider(50:50:ag_number_evals))
"""
end

# ╔═╡ 2af35bfb-b24f-4210-a0a1-af4879ced7f9
md"""
# AG Generacional Vs AG Estacionario

Vamos a comparar los resultados de ambos para el problema **$(basename(fname))** con **$(ag_number_evals)** evaluaciones.
"""

# ╔═╡ 482a3d43-77b0-4f1a-b2ad-c9ded08f0226
md"""
# Operadores Comunes
"""

# ╔═╡ bffa1ef7-b779-46ae-9306-3364aaf0e729
md"""
## Crear una solución

Para crear una solución desordenamos un vector de índices.
"""

# ╔═╡ 7d4b2a03-b544-4e7b-a096-a2f97dcaddfa
function indices_ordenados(vector)
	return sortperm(vector)
end

# ╔═╡ d098ac9b-526e-47a6-963f-a61b5265e886
"""
	new_solution(N)

Permite generar una nueva solución/permutación de tamaño N.

### Parametros: 
- N: Tamaño de la solución.
"""
function new_solution(N)
	return shuffle(1:N)
end

# ╔═╡ acfbad57-b07e-48b4-bb92-ef35350240b7
md"""
Vamos a ver varios ejemplos:
"""

# ╔═╡ a647901b-50e1-4430-a85c-2b50c8eae0ff
for _ in 1:5
	local nueva_solucion = new_solution(10)
	@show nueva_solucion
end

# ╔═╡ f890be4d-60db-4424-99ab-0286ef9b47dd
md"""
## Evaluar una solución

El siguiente código muestra cómo se puede evaluar una solución.
"""

# ╔═╡ 307784a8-a5f1-4d1c-b228-6c76d26bd863
"""
	fitness(solution)

Devuelve la longitud de la solución pasada por parámetro.

### Parametros:

- solution: Solución a evaluar.

### Devuelve: La distancia (como valor real).

"""
function fitness(solution)
	distances = Distances_cities
	total = 0.0
	tam = length(solution)

	# Voy sumando los resultados de cada tramo del trayecto
	for i in 1:(tam-1)
		total += distances[solution[i],solution[i+1]]
	end
	# Le sumo la distancia de la última a la primera
	total += distances[solution[tam],solution[1]]
	return total
end

# ╔═╡ 76bad016-e20e-4491-b7e2-c47b7eec0a20
begin
	function plot_sol(sol; title="")
		positions = Position_cities
		fit_sol = fitness(sol)
		if isempty(title)
			title = "Fitness: $(round(fit_sol, digits=2))"
		end
		plt = plot_TSP(Dict(:markersize=>3, :color=>:black, :title=>title))
		for i in 1:(length(sol)-1)
			ant = sol[i]
			next = sol[i+1]
			plot!(plt, positions[1,[ant,next]], positions[2,[ant,next]], color=:gray, style=:dash, linealpha=3)
		end
		plot!(plt, positions[1,[sol[end],sol[begin]]], positions[2,[sol[end],sol[begin]]], color=:gray, style=:dash, linealpha=0.5)
		plt
	end
	md"""
Vamos a visualizar soluciones aleatorias $(@bind boton_new Button(\"Nueva Aleatoria\"))
"""
end

# ╔═╡ ac6d750a-658d-4357-b912-4569c61e23ac
begin
	boton_new
	local solution = new_solution(N)
	plot_sol(solution)
end

# ╔═╡ cb7e1e27-f497-47cb-9fac-1f96c19c99f3
md"""
## Mutación de una solución

Consideramos que si una solución muta se intercambian dos posiciones aleatorias.
"""

# ╔═╡ dfd2a922-c497-47f5-992f-d23ae107683b
"""
	mutation(solution)

Muta una solución cambiando dos posiciones aleatorias.

### Parámetros:
- solution: Solución a mutar.

### Devuelve: Nueva solución mutada.
"""
function mutation(solution; verbose=false)
	dim = length(solution)
	pos1, pos2 = samplepair(1:dim)

	if verbose
		@debug "Intercambio posiciones $pos1 y $pos2"
	end
	mutation_sol = copy(solution)
	mutation_sol[pos2], mutation_sol[pos1] = solution[pos1], solution[pos2]
	return mutation_sol
end

# ╔═╡ 170b110d-d1f2-4d3c-a1f7-cf7ac6075a69
md"Vamos a mostrar un ejemplo $(@bind boton_muta Button(\"Muta aleatorio\"))"

# ╔═╡ 40df03c1-78d5-4720-a00a-c0ed749fdc85
begin
	boton_muta
	local solution = new_solution(10)
	mutated_solution = mutation(solution, verbose=true)
	@debug "Original: $solution"
	@debug "Tras Mutar: $mutated_solution"
	nothing
end

# ╔═╡ 5be982d9-0e21-44e7-91e9-34d9ae6b1a2b
md"Vamos a mostrarlo visualmente $(@bind visual_mutacion Button(\"Mostrar mutación\"))"

# ╔═╡ c940c590-18a4-4885-9cc0-54f5b11d64b9
begin 
	function plot_cities!(plot, solution, posi; color=:red)
		positions = Position_cities
		scatter!(plot, positions[1,solution[posi]], positions[2,solution[posi]], color=color)
	end
	function plot_edge!(plot, solution, posi; color=:red)
		dim = length(solution)
		positions = Position_cities
		newposi = ifelse(posi < dim, posi+1, 1)
		prevposi = (posi > 1 ? posi - 1 : dim)
		plot
		plot!(plot, positions[1, solution[[posi, newposi]]], positions[2, solution[[posi,newposi]]], color=color)
		plot!(plot, positions[1, solution[[prevposi, posi]]], positions[2, solution[[prevposi,posi]]], color=color)
	end
	function plot_mutation(solution)
		sol = solution
		dim = length(solution)
		pos1, pos2 = samplepair(1:dim)
		newsolution = copy(solution)
		newsolution[[pos2,pos1]] = solution[[pos1, pos2]]
		
		p1 = plot_sol(solution; title="Solución Original")
		p2 = plot_sol(newsolution; title="Solución Cambiada")

		@animate for i in 1:5
			if i == 1
				p1 = plot_sol(solution; title="Solución Original")
				p1
			elseif i == 2
				plot_cities!(p1, solution, [pos1, pos2]; color=:red)
				p1
			elseif i == 3
				plot_edge!(p1, solution, pos1, color=:orange)
				plot_edge!(p1, solution, pos2, color=:orange)
				p1
			elseif i == 4
				plot_cities!(p2, newsolution, [pos1, pos2]; color=:green)
				plot_edge!(p2, newsolution, pos1, color=:green)
				plot_edge!(p2, newsolution, pos2, color=:green)
				p2
			else
				plot_sol(newsolution; title="Solución Final")
			end
		end
	end

	visual_mutacion
	anim = plot_mutation(new_solution(N))
	gif(anim, "anim_mutation.gif", fps = 0.5, loop=0, show_msg=false)
	#PlutoUI.LocalResource("anim_fps15.gif")
end

# ╔═╡ f8992c2b-62f5-4a9b-8801-3fb99a8dfc3d
md"""
## Mecanismo de Selección

Para seleccionar una solución vamos a elegir aleatoriamente dos muestras, y vamos a elegir la que presenta mejor fitness. 
"""

# ╔═╡ dbe29c8e-0c89-42f3-9e98-c1ea854b1bfc
"""
	torneo_binario(vector_fitness)

Devuelve la posición ganadora de un torneo binario.

### Parametros:
- vector_fitness: Vector de fitness de las soluciones de las que seleccionar.
- verbose: Indica si se desea salida para depurar (false por defecto).

### Devuelve: posición ganadora.
"""
function torneo_binario(vector_fitness; verbose=false)
	dim = length(vector_fitness)
	pos1 = rand(1:dim)
	pos2 = rand(1:dim)

	# Debe de ser distinto
	while pos2 == pos1
		pos2 = rand(1:dim)
	end

	if verbose
		@debug "Posiciones: $pos1, $pos2"
		@debug "Fitness: $(vector_fitness[pos1]), $(vector_fitness[pos2])"
	end
	
	result = 0

	if vector_fitness[pos1] < vector_fitness[pos2]
		result = pos1
	else
		result = pos2
	end

	return result
end

# ╔═╡ eacab210-b42e-4606-9e86-a6b882cdba6e
md"""
Ejemplo de uso: $(@bind boton_torneo Button(\"Aplica Torneo\"))
"""

# ╔═╡ ba092a34-a5f9-47ba-ace4-b83570c5b717
begin
	boton_torneo
	local vector_fitness = [3, 8, 2, 5, 10, 7, 4]
	local posi = torneo_binario(vector_fitness, verbose=true)
	@debug "Ganador: $posi"
end

# ╔═╡ 2571484f-21ce-45af-bace-4fc4cec62089
md"""
## Operador de Cruce

Para este problema vamos a aplicar el operador OX ya que para este problema es el que da mejor problema, como se ve en el trabajo que [compara distintos operadores de cruce](https://arxiv.org/ftp/arxiv/papers/1203/1203.3097.pdf). 

Este operador OX es el _Ordered Crossover_ (operador de orden) que se caracteriza en que más que intentar mantener de las soluciones originales las posiciones de aparición de las ciudades busca mantener el orden entre sí.

$(RobustLocalResource(\"https://creationwiki.org/pool/images/thumb/d/dc/Ox.png/300px-Ox.png\", "OX.png")).

La idea es la siguiente, dadas dos soluciones se intercambia un segmento elegido aleatoriamente, y el resto de ciudades se van copiando (ignorando las existentes) en el mismo orden. 
"""

# ╔═╡ fa9c4523-c9c0-4ab2-98d1-3e65397e6bd6
md"""
Nos faltan algunas funciones por implementar.
"""

# ╔═╡ 99d32178-8984-403b-8052-e3398b3b8b65
"""
	add_rotate(valor, tope)

Permite incrementar el valor, volviendo al primer valor si se supera el límite.

### Parámetros:
- value: valor a incrementar.
- tope: valor máximo.
"""
function add_rotate(valor, tope)
	if valor == tope
		return 1
	else
		return valor+1
	end
end

# ╔═╡ 9285c1b5-7599-4568-b946-2e39290ef0ff
md"""
Vamos a probarlo con unos pocos ejemplos.
"""

# ╔═╡ de419343-3685-445b-a3de-b94f46008c60
begin
	@test add_rotate(1, 4) == 2
	@test add_rotate(2, 4) == 3
	@test add_rotate(3, 4) == 4
	@test add_rotate(4, 4) == 1
end

# ╔═╡ ddaac93b-0c84-4675-9b29-bab93014283d
"""
	rellena_resto(sol, newsol, inicio)

Rellena newsol con los valores de sol desde la posición inicio, ignorando los ya existentes.
"""
function rellena_resto(sol, newsol, inicio)
	dim = length(sol)
	pos_src = inicio
	pos_dst = inicio
	num = count(!iszero, newsol)
	# @assert iszero(newsol[inicio])
	
	while num < dim
		if sol[pos_src] ∉ newsol
			newsol[pos_dst] = sol[pos_src]
			pos_dst = add_rotate(pos_dst, dim)
			num += 1
		end
		pos_src = add_rotate(pos_src, dim)
	end
	return newsol
end

# ╔═╡ 8babcf71-6c3a-49d6-bdb1-e2601bb6bf5f
"""
	crossover_OX(sol1, sol2)

Aplica el cruce entre las soluciones sol1 y sol2, devolviendo dos nuevas soluciones.

### Parámetros:

- sol1: Primera solución.
- sol2: Otra solución.
- verbose: Indica si se desea información.

### Devuelve: un par de soluciones.
"""
function crossover_OX(sol1, sol2, verbose=false)
	dim = length(sol1)
	# Obtengo un par aleatorio
	pos1, pos2 = samplepair(dim) 

	# Me aseguro que pos1 sea menor que pos2
	if pos1 > pos2
		pos1, pos2 = pos2, pos1
	end

	if verbose
		@debug pos1
		@debug pos2
	end

	# Creo memoria
	newsol1 = zeros(Int, dim)
	newsol2 = zeros(Int, dim)

	# Intercambio el rango
	for i ∈ pos1:pos2
		newsol1[i] = sol2[i]
		newsol2[i] = sol1[i]
	end

	# Incrementa la siguiente posición
	inicio = add_rotate(pos2, dim)
	# Relleno el resto de elementos
	newsol1 .= rellena_resto(sol1, newsol1, inicio)
	newsol2 .= rellena_resto(sol2, newsol2, inicio)
	return newsol1, newsol2
end

# ╔═╡ 4afbe858-3f79-4061-94f5-657e8e36172a
begin
	local sol_rellenada = rellena_resto([1, 3, 2, 4], [0, 1, 2, 0], 4)
	@test all(sol_rellenada .== [3, 1, 2, 4])
	local sol_dibujo = rellena_resto([7, 5, 3, 1, 9, 8, 6, 4, 2], [0, 0, 0, 8, 5, 7, 3, 0, 0], 8)
	@test all(sol_dibujo .== [1, 9, 6, 8, 5, 7, 3, 4, 2])
end

# ╔═╡ a5f2720c-edfb-414a-9bb1-6957b8c6fa81
begin
	local sol1 = new_solution(10)
	local sol2 = new_solution(10)
	local newsol1, newsol2 = crossover_OX(sol1, sol2)
	@test all(crossover_OX(sol1, sol1) .== (sol1, sol1))
end

# ╔═╡ 5f487255-3171-4b50-9e38-fe4146c4115a
md"""
## Reemplazo del AG Estacionario
"""

# ╔═╡ e2b71cc7-e505-4ea1-84dd-6109ec49204c
"""
	reemplaza_peores(newsol1, fitness_sol1, newsol2, fitness_sol2, 
						pop, fitness_pop)

Reemplaza las dos peores soluciones por las nuevas si las mejoran.

### Parámetros:

- newsol1: Primera nueva solución.
- fitness_sol1: Fitness de newsol1.
- newsol2: La otra nueva solución.
- fitness_sol2: Fitness de newsol2.
- pop: Población actual **(es modificada)**.
- fitness_pop: Vector de fitness **(es modificada)**.
"""
function reemplaza_peores!(newsol1, fitness_sol1, newsol2, fitness_sol2, pop, fitness_pop)
	posi_ordenados = indices_ordenados(fitness_pop)
	pos_worst = posi_ordenados[end]
	pos_second_worst = posi_ordenados[end-1]
	worst = pop[pos_worst,:]
	second_worst = pop[pos_second_worst,:]
	minipop_fit = [fitness_sol1, fitness_sol2, fitness_pop[pos_worst], fitness_pop[pos_second_worst]]
	minipop = [newsol1, newsol2, worst, second_worst]
	selected = indices_ordenados(minipop_fit)
	# Reemplazo los dos peores
	pop[pos_worst, :] .= minipop[first(selected)] 
	fitness_pop[pos_worst] = minipop_fit[first(selected)]
	pop[pos_second_worst, :] .= minipop[selected[2]] 
	fitness_pop[pos_second_worst] = minipop_fit[selected[2]]
	nothing
end

# ╔═╡ a4e30c13-e7a6-406e-b8d2-16758231b7ff
begin
	sol1 = [1, 2, 3]
	sol2 = [2, 3, 4]
	pop = zeros(Int, 3, 3)
	fitness_pop = [6, 8, 4]
	reemplaza_peores!(sol1, 3, sol2, 7, pop, fitness_pop)
	@test all(sort(fitness_pop) .== [3, 4, 6])
	pop = zeros(Int, 3, 3)
	fitness_pop = [6, 8, 4]
	reemplaza_peores!(sol1, 9, sol2, 10, pop, fitness_pop)
	@test all(sort(fitness_pop) .== [4, 6, 8])
end

# ╔═╡ 4e9cd677-60f5-4d0b-b882-7c7666f8d5ff
md"""
## Apéndice

Celdas ocultas.
"""

# ╔═╡ e4c005e3-d1bd-47e3-9f66-105931a45f34
begin
	eachsol(pop)=eachrow(pop)
	indices(pop::AbstractVector{T}) where T=eachindex(pop)
	indices(matrix::Matrix{T}) where T=1:size(matrix, 1)
	posicion_aleatoria(pop)=rand(1:size(pop, 1))
	con_probabilidad(prob)=rand() <= prob
	pos_mejor(fit)=argmin(fit)
	pos_peor(fit)=argmax(fit)
	obten_mejor_fitness(fit)=minimum(fit)
	nothing
end

# ╔═╡ 12a0eb6e-080b-442f-aa7b-67be6a13c2d2
function AGG(dimension, popsize, pcross, pmut; maxevals=50_000, historico=Tuple{Int,AbstractVector{<:Integer},Float64}[], copia_historico=false)
	pop = zeros(Int, popsize, dimension)
	# Creo la nueva población
	newpop = copy(pop)
	
	# Inicializo el vector
	for i in 1:popsize
		pop[i,:] .= new_solution(dimension)
	end

	# Vector de fitness
	fitness_pop = [fitness(sol) for sol in eachsol(pop)]
	mejor = argmin(fitness_pop)
	# Inicio el número de evaluaciones
	evals = popsize

	if copia_historico
		push!(historico, (evals, pop[argmin(fitness_pop), :], obten_mejor_fitness(fitness_pop)))
	end
	
	while evals < maxevals
		# Aplico selección por torneo
		for i in indices(newpop)
			# Copio el ganador del torneo
			posi = torneo_binario(fitness_pop)
			newpop[i, :] .= pop[posi, :]
		end

		# Empiezo a cruzar de forma consecutiva
		total_cruzar = (popsize*pcross)
		i = 1

		while i < total_cruzar
			sol1 = newpop[i, :]
			sol2 = newpop[i+1, :]
			newsol1, newsol2 = crossover_OX(sol1, sol2)
			newpop[i, :] .= newsol1
			newpop[i+1, :] .= newsol2
			i += 2
		end

		# Mutación
		total_mutar = popsize ÷ 10

		for i in enumerate(total_mutar)
			posi = posicion_aleatoria(newpop)
			newpop[posi, :] .= mutation(newpop[posi, :])
		end
		
		# Evaluación
		fitness_newpop = [fitness(sol) for sol in eachsol(newpop)]
		evals += popsize

		# Elitismo, no permito que empeore
		if fitness_pop[mejor] < obten_mejor_fitness(fitness_newpop)
			worst = pos_peor(fitness_newpop)
			newpop[worst, :] .= pop[mejor, :]
			fitness_newpop[worst] = fitness_pop[mejor]
		end

		# Reemplazo
		pop .= newpop
		fitness_pop .= fitness_newpop
		mejor = pos_mejor(fitness_pop)
		
		if copia_historico
			push!(historico, (evals, pop[mejor, :], fitness_pop[mejor]))
		end
	
	end

	return pop[mejor, :], fitness_pop[mejor]
end

# ╔═╡ 73dc306d-3904-4c35-899c-05823e2380f2
function AGE(dimension, popsize, p_mut; maxevals=50_000, historico=Tuple{Int, AbstractVector{Integer}, Float64}[], copia_historico=false)
	pop = zeros(Int, popsize, dimension)
	
	# Inicializo el vector
	for i in 1:popsize
		pop[i, :] .= new_solution(dimension)
	end

	# Vector de fitness
	fitness_pop = [fitness(sol) for sol in eachsol(pop)]
	# Inicio el número de evaluaciones
	evals = popsize

	if copia_historico
		push!(historico, (evals, pop[pos_mejor(fitness_pop), :], obten_mejor_fitness(fitness_pop)))
	end
	
	@views while evals < maxevals
		# Aplico selección por torneo
		posi1 = torneo_binario(fitness_pop)
		posi2 = torneo_binario(fitness_pop)

		# Cruco las soluciones aleatorias
		newsol1, newsol2 = crossover_OX(pop[posi1, :], pop[posi2, :])

		# Mutación
		if (con_probabilidad(p_mut))
			newsol1 .= mutation(newsol1)
		end

		if (con_probabilidad(p_mut))
			newsol2 .= mutation(newsol2)
		end
		
		# Evaluación
		fitness_sol1 = fitness(newsol1)
		fitness_sol2 = fitness(newsol2)
		evals += 2
			
		# Reemplazo las dos peores
		reemplaza_peores!(newsol1, fitness_sol1, newsol2, fitness_sol2, pop, fitness_pop)
		
		if copia_historico
			push!(historico, (evals, pop[pos_mejor(fitness_pop), :], obten_mejor_fitness(fitness_pop)))
		end
	end

	mejor = pos_mejor(fitness_pop)
	return pop[mejor, :], fitness_pop[mejor]
end

# ╔═╡ 721acdea-79c6-4409-9e52-06f66ebf67d7
begin 
	function AGE_One(dimension, popsize, p_mut; maxevals=50_000, historico=Tuple{Int, AbstractVector{Integer}, Float64}[], copia_historico=false)
	pop = zeros(Int, popsize, dimension)
	
	# Inicializo el vector
	for i in 1:popsize
		pop[i, :] .= new_solution(dimension)
	end

	# Vector de fitness
	fitness_pop = [fitness(sol) for sol in eachsol(pop)]
	# Inicio el número de evaluaciones
	evals = popsize
	pos_worst = argmax(fitness_pop)

	if copia_historico
		push!(historico, (evals, pop[argmin(fitness_pop), :], minimum(fitness_pop)))
	end
	
	@views while evals < maxevals
		# Aplico selección por torneo
		posi1 = torneo_binario(fitness_pop)
		posi2 = torneo_binario(fitness_pop)

		# Cruco las soluciones aleatorias
		newsol1, newsol2 = crossover_OX(pop[posi1, :], pop[posi2, :])

		# Mutación
		if (rand() <= p_mut)
			newsol1 .= mutation(newsol1)
		end

		if (rand() <= p_mut)
			newsol2 .= mutation(newsol2)
		end
		
		# Evaluación
		fitness_sol1 = fitness(newsol1)
		fitness_sol2 = fitness(newsol2)
		evals += 2

		if fitness_sol1 < fitness_sol2
			fitness_sol = fitness_sol1
			sol = newsol1
		else
			fitness_sol = fitness_sol2
			sol = newsol2
		end
		# Reemplazo el peor
		if fitness_sol < fitness_pop[pos_worst]
			pop[pos_worst, :] .= sol
			fitness_pop[pos_worst] = fitness_sol
			pos_worst = argmax(fitness_pop)
		end
	
		if copia_historico
			push!(historico, (evals, pop[argmin(fitness_pop), :], minimum(fitness_pop)))
		end
	end

	mejor = argmin(fitness_pop)
	return pop[mejor, :], fitness_pop[mejor]
end
	nothing
end

# ╔═╡ a8657d4f-867b-43b3-8e78-8be73f1ff8ea
begin
	historico_agg = Tuple{Int,Vector{Int},Float64}[]
	historico_age = Tuple{Int,Vector{Int},Float64}[]
	historico_age_one = Tuple{Int,Vector{Int},Float64}[]
	
	seed!(seed_value)
	
	if isempty(online)
		time_agg = @elapsed _, _ = AGG(N, 50, 0.7, 0.1; maxevals=ag_number_evals, copia_historico=true, historico=historico_agg)
		seed!(seed_value)
		time_age = @elapsed _, _ = AGE(N, 50, 0.1; maxevals=ag_number_evals, copia_historico=true, historico=historico_age)
		time_age_one = @elapsed _, _ = AGE_One(N, 50, 0.1; maxevals=ag_number_evals, copia_historico=true, historico=historico_age_one)
	end
	nothing
end

# ╔═╡ bce56ce3-fb2e-4d64-bb2b-97f85a00aa94
begin
	local sol, fit
	if !isempty(online)
		seed!(seed_value)
		(sol, fit) = AGG(N, 50, 0.7, 0.1; maxevals=global_evals_agg)
	else
		encuentra_historico_agg(item)=first(item)>=global_evals_agg
		local item = findfirst(encuentra_historico_agg, historico_agg)
		(_, sol, fit) = historico_agg[item]
	end
	local evals_gga_str = @sprintf "%.2E" global_evals_agg
	plot_sol(sol; title="Resultados AGG: $(evals_gga_str) evals, distancia $(round(fit, digits=1))")
end

# ╔═╡ 05934fbf-e9a3-41e4-a333-18be8eda1275
begin
	if !isempty(historico_agg)
		local x = first.(historico_agg)
		local y = last.(historico_agg)
		plot(x, y, legend=false, xlabel="Evaluaciones", ylabel="Fitness", yscale=:log10, title="Gráfica de Convergencia del AG Generacional")
	end
end

# ╔═╡ 16a2aa78-c2d0-4fbc-88e4-fb45032aa14e
begin
	local sol, fit
	if !isempty(online)
		seed!(seed_value)
		(sol, fit) = AGE(N, 50, 0.1; maxevals=global_evals_age)
	else
		encuentra_historico_age(item)=first(item)>=global_evals_age
		local item = findfirst(encuentra_historico_age, historico_age)
		local sol, fit
		(_, sol, fit) = historico_age[item]
	end
	local evals_gga_str = @sprintf "%.2E" global_evals_age
	plot_sol(sol; title="Resultados AGE: $(evals_gga_str) evals, distancia $(round(fit, digits=1))")
end

# ╔═╡ 3be68ad7-75a1-4a4d-a234-2bd24418b963
begin
	if !isempty(historico_age)
		local x = first.(historico_age)
		local y = last.(historico_age)
		plot(x, y, legend=false, xlabel="Evaluaciones", ylabel="Fitness", yscale=:log10, title="Gráfica de Convergencia del AG Estacionario")
	end
end

# ╔═╡ e5846c20-63aa-4972-9d00-5839ce9f2128
begin
	local sol_agg, sol_age, fit_agg, fit_age
	local item_age, item_agg
	if isempty(online)

		encuentra_historico_ag(item)=first(item)>=global_evals_ag
		item_age = findfirst(encuentra_historico_ag, historico_age)
		(_, sol_age, fit_age) = historico_age[item_age]
		item_agg = findfirst(encuentra_historico_ag, historico_agg)
		(_, sol_agg, fit_agg) = historico_agg[item_agg]
	local evals_gg_str = @sprintf "%.2E" global_evals_ag
	p_age = plot_sol(sol_age; title="Resultados AGE: $(evals_gg_str) evals, distancia $(round(fit_age, digits=1))")
	p_agg = plot_sol(sol_agg; title="Resultados AGG: $(evals_gg_str) evals, distancia $(round(fit_agg, digits=1))")
	md"""
	$(p_agg)
	$(p_age)
	"""
	end
	
end

# ╔═╡ f512edb8-95ec-485d-9037-81c1062933c1
begin
	local best_agg, best_age, best_age_one
	(_, _, best_agg) = last(historico_agg)
	(_, _, best_age) = last(historico_age)
	(_, _, best_age_one) = last(historico_age_one)
	df = DataFrame("Algoritmo"=>String[], "Mejor Fitness"=>Float64[], "Tiempo" =>Float64[])
	push!(df, ("Generacional", best_agg, time_agg))
	push!(df, ("Estacionario", best_age, time_age))
	# push!(df, ("Estacionario One", best_age_one, time_age_one))
	df
end

# ╔═╡ Cell order:
# ╟─3d1cc3c8-dc80-11ed-3163-9d457a2fc8f2
# ╟─f8623f68-7151-4416-9ffe-87d704ce0aff
# ╟─421c26f4-e9fe-4f53-917f-4ade85d96cc7
# ╟─ab1e47c3-3dab-4982-a7ec-7fdd196f5d24
# ╟─ba86256b-134b-4309-88ad-4bf9296c7d42
# ╟─903c9853-acdc-4495-855d-3d4ce2242bf3
# ╟─85e41585-b696-42e7-80d5-0c980a30a536
# ╟─929dbc59-8d47-438c-aa6b-a797cf8cdb73
# ╟─04437555-ddb3-49b6-98cc-cf5687af4c08
# ╟─08bec682-efa6-4bc0-b739-0ddd02f8f0d8
# ╠═12a0eb6e-080b-442f-aa7b-67be6a13c2d2
# ╟─6f75ee5e-8b40-42ae-b59f-fc17a2c16800
# ╠═73dc306d-3904-4c35-899c-05823e2380f2
# ╟─e07d5db1-fedb-4883-9e7b-42bbeb1196c4
# ╟─e8ccadcf-ae4d-4014-a3bc-0d08b1c7fb58
# ╟─441219bc-c438-4159-ad1e-8441cdd850e9
# ╟─4e1cf32a-9387-4b6b-b324-d5ecb14e614d
# ╟─abb709a1-7344-4e84-a24f-443caed0fc00
# ╟─bce56ce3-fb2e-4d64-bb2b-97f85a00aa94
# ╟─05934fbf-e9a3-41e4-a333-18be8eda1275
# ╟─1ca679ff-faf5-4194-9da3-3f8811bb3049
# ╟─16a2aa78-c2d0-4fbc-88e4-fb45032aa14e
# ╟─3be68ad7-75a1-4a4d-a234-2bd24418b963
# ╟─ddb0cea0-dfd7-40a7-a6c3-8dbb68c042d3
# ╟─e5846c20-63aa-4972-9d00-5839ce9f2128
# ╟─2af35bfb-b24f-4210-a0a1-af4879ced7f9
# ╟─f512edb8-95ec-485d-9037-81c1062933c1
# ╟─482a3d43-77b0-4f1a-b2ad-c9ded08f0226
# ╟─bffa1ef7-b779-46ae-9306-3364aaf0e729
# ╟─7d4b2a03-b544-4e7b-a096-a2f97dcaddfa
# ╠═d098ac9b-526e-47a6-963f-a61b5265e886
# ╟─acfbad57-b07e-48b4-bb92-ef35350240b7
# ╠═a647901b-50e1-4430-a85c-2b50c8eae0ff
# ╟─76bad016-e20e-4491-b7e2-c47b7eec0a20
# ╟─ac6d750a-658d-4357-b912-4569c61e23ac
# ╟─f890be4d-60db-4424-99ab-0286ef9b47dd
# ╠═307784a8-a5f1-4d1c-b228-6c76d26bd863
# ╟─cb7e1e27-f497-47cb-9fac-1f96c19c99f3
# ╟─dfd2a922-c497-47f5-992f-d23ae107683b
# ╟─170b110d-d1f2-4d3c-a1f7-cf7ac6075a69
# ╟─40df03c1-78d5-4720-a00a-c0ed749fdc85
# ╟─5be982d9-0e21-44e7-91e9-34d9ae6b1a2b
# ╟─c940c590-18a4-4885-9cc0-54f5b11d64b9
# ╟─f8992c2b-62f5-4a9b-8801-3fb99a8dfc3d
# ╟─dbe29c8e-0c89-42f3-9e98-c1ea854b1bfc
# ╟─eacab210-b42e-4606-9e86-a6b882cdba6e
# ╟─ba092a34-a5f9-47ba-ace4-b83570c5b717
# ╟─2571484f-21ce-45af-bace-4fc4cec62089
# ╟─8babcf71-6c3a-49d6-bdb1-e2601bb6bf5f
# ╟─fa9c4523-c9c0-4ab2-98d1-3e65397e6bd6
# ╟─99d32178-8984-403b-8052-e3398b3b8b65
# ╟─9285c1b5-7599-4568-b946-2e39290ef0ff
# ╠═de419343-3685-445b-a3de-b94f46008c60
# ╟─ddaac93b-0c84-4675-9b29-bab93014283d
# ╟─4afbe858-3f79-4061-94f5-657e8e36172a
# ╟─a5f2720c-edfb-414a-9bb1-6957b8c6fa81
# ╟─5f487255-3171-4b50-9e38-fe4146c4115a
# ╟─e2b71cc7-e505-4ea1-84dd-6109ec49204c
# ╟─a4e30c13-e7a6-406e-b8d2-16758231b7ff
# ╟─4e9cd677-60f5-4d0b-b882-7c7666f8d5ff
# ╟─a8657d4f-867b-43b3-8e78-8be73f1ff8ea
# ╟─e4c005e3-d1bd-47e3-9f66-105931a45f34
# ╟─721acdea-79c6-4409-9e52-06f66ebf67d7
