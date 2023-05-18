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

# ╔═╡ 5ccf83de-10cd-46e0-b940-664b67831e48
begin
	using Pkg
	Pkg.activate(".")
	using PlutoUI
	import Distances
	using Plots
	using Random: shuffle, seed!
	using PlutoTeachingTools
	using DataFrames
	PlutoTeachingTools.set_language!(PlutoTeachingTools.get_language_from_env())
	PlutoUI.TableOfContents(title="📚 Índice", indent=true)
end

# ╔═╡ 0e1d1860-943a-4808-834f-833e15bc0396
html"""<style>
main {
    max-width: 1000px;
}
"""

# ╔═╡ f78d4556-c30e-11ed-3cc3-ffa49c1c0da9

md"# Resolviendo el TSP con Metaheurísticas, Parte 1"

# ╔═╡ 63967850-2682-4d70-89cf-76d91d5da628
md"""
## Sobre este documento

Este documento forma parte del **Proyecto de Innovación Docente Desarrollo de herramientas web interactivas para el aprendizaje de Metaheurísticas** asociado a la asignatura de Metaheurísticas que se imparte para el _Grado en Ingeniería Informática_ (aunque abierta a grados dobles) en la **Universidad de Granada (UGR)**.
"""

# ╔═╡ 8ff8d174-7651-493a-94ba-c613fd7ff69b
md"""
En este sistema interactivo se mostrará cómo se puede aplicar un problema concreto, el _Viajante de Comercio_ para resolverlo con distintas metaheurísticas, algo semejante a lo que tienen que hacer los y las estudiantes de la asignatura, pero con problemas distintos. Al igual que las prácticas de la asignatura, este entorno web está dividido en tres partes, cada una de ellas abordando distintas metaheurísticas sobre el mismo problema.
"""

# ╔═╡ 4b016a19-3e60-429c-a52b-9a7415bbb808
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

	Hay recursos _online_ para ver ciertas [diferencias entre Python y Julia](https://towardsdatascience.com/moving-code-from-python-to-julia-beware-of-false-friends-160573a5d552), pero no es necesario profundizar para entender los algoritmos y "_jugar_", si se quiere, con el código. 
"""

# ╔═╡ d09d69b4-16b6-4bc4-ac73-209d4599fcce
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

# ╔═╡ 13528697-092b-43f8-b6e3-12e4cbc12559
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

# ╔═╡ 37c8cf4b-eed8-428f-b181-36727af9d472
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
			distances = Distances.pairwise(Distances.Euclidean(), position_cities, dims=2)
			return N, position_cities, distances
		end
	end
end

# ╔═╡ dbb838ef-262a-4db4-8bae-5e8332fba3a6
md"Vamos a leer sus datos (suponiendo que existe la fución **read_TSP** que devuelve el tamaño, las posiciones (para pintar visualmente) y las distancias entre ellas (calculadas como las distancias euclídeas a partir de sus posiciones):"

# ╔═╡ 02fcaf7d-7fe5-48f6-83ba-5387e342892d
N, Position_cities, Distances_cities = read_TSP(fname);

# ╔═╡ d80dd12d-c9d8-4dc1-b42d-ecb746b98101
md"Vamos a visualizar el problema:"

# ╔═╡ 80eef61f-1414-4aeb-86de-416263797d29
begin
	function plot_TSP(position_cities, options=Dict{}())
		scatter(position_cities[1,:], position_cities[2,:]; title=description(fname), legend=false, axis=false, options...)
	end
	plot_TSP(Position_cities)
end

# ╔═╡ 3315e650-cf41-4bd9-96f1-e548a19f7f44
md"""
## Representación del problema

Por comodidad usaremos como representación del problema el orden en el que las ciudades son recorridas. Y supondremos que vuelve de la última ciudad a la primera.

Esto implica que toda permutación entre 1 y $(N) será una solución válida para el problema.

Por ejemplo, si tenemos la solución aleatoria: $(@bind go Button(\"Genera solución\"))
"""

# ╔═╡ 251fbc45-c637-4652-ad50-01d40ce2537c
begin
	go
	sol = shuffle(1:N)
end

# ╔═╡ 88d163e8-1f21-48a4-9ae6-2bb217b7cff3
md"Visualmente sería"

# ╔═╡ 66183a3b-11e7-4c92-8784-714b5d22738e
begin
	function plot_sol(positions, sol, fit_sol=missing)
		if ismissing(fit_sol)
			title = "Solution to $(description(fname))"
		else
			title = "Fitness: $(round(fit_sol, digits=2))"
		end
		plt = plot_TSP(positions, Dict(:markersize=>3, :color=>:black, :title=>title))
		for i in 1:(length(sol)-1)
			ant = sol[i]
			next = sol[i+1]
			plot!(plt, positions[1,[ant,next]], positions[2,[ant,next]], color=:gray, style=:dash, linealpha=0.5)
		end
		plot!(plt, positions[1,[sol[end],sol[begin]]], positions[2,[sol[end],sol[begin]]], color=:gray, style=:dash, linealpha=0.5)
		plt
	end

	plot_sol(Position_cities, sol)
end

# ╔═╡ 0daabc72-3ef2-488d-8f6e-aefd2cae841d
md"""
## Evaluando una solución

En este apartado vamos a ver cómo podemos evaluar una solución. 

Para ello, definiremos una función que reciba las distancias y la solución, y haga todas las sumas.
"""

# ╔═╡ f6d62ede-1e5e-41e1-9981-909f070d63fb
function fitness(distances, sol)
	total = 0.0
	tam = length(sol)

	for i in 1:(tam-1)
		total += distances[sol[i],sol[i+1]]
	end
	total += distances[sol[tam],sol[1]]
	return total
end

# ╔═╡ 9aa54296-488d-4808-b457-a64ab8fd566c
md"Lo probamos:"

# ╔═╡ 2be1750b-85d5-4b98-a4f0-4148285cb058
fitness(Distances_cities, sol)

# ╔═╡ 668baf12-9a75-4ec6-903e-236ab69066a5
md"Ahora vamos a añadirlo a la visualización:"

# ╔═╡ 1792f776-9916-402f-9de3-5716ed6744e9
plot_sol(Position_cities, sol, fitness(Distances_cities, sol))

# ╔═╡ ec6be0aa-e367-49cf-a3d4-cfc1e69602e0
md"""
## Generando soluciones de forma aleatoria

Como valor de referencia vamos primero a intentar obtener la solución generando soluciones de forma totalmente aleatoria, y luego compararemos con el resto de algoritmos.
"""

# ╔═╡ 87f6103e-be1f-404b-ab36-7ae68231ebed
md"El primer paso es indicar el número de evaluaciones (_maxevals_) que queremos: $(@bind maxevals NumberField(100:50000, default=1000))"

# ╔═╡ efdb8e91-8c36-4990-a18a-be37572de341
md"El código para generar _maxevals_ soluciones aleatorias es el siguiente"

# ╔═╡ 498c1ce3-ef85-4472-b568-d7f95710c1f5
md"En donde *inicia_sol* se crea de forma totalmente aleatoria"

# ╔═╡ b810106c-6b18-4670-94e9-976cf56c2ab5
function inicia_sol(n)
	return shuffle(1:n)
end

# ╔═╡ 55c3e565-c98d-4235-a503-2a3fc6f2ef9a
function optim_random(distancias, maxevals)
	n = size(distancias, 1)
	best = inicia_sol(n)
	best_fit = fitness(distancias, best)
	evals = 1

	while evals < maxevals
		newsol = inicia_sol(n)
		fit_new = fitness(distancias, newsol)

		if fit_new < best_fit
			best = newsol
			best_fit = fit_new
		end
		evals += 1
	end

	return best, best_fit
end

# ╔═╡ a0ea972b-1cbf-4f52-a6cc-20f0a66700b2
md"Vamos a probarlo"

# ╔═╡ 8fb74b55-4a82-4eb7-bdcf-d63fa4cf3be4
begin
	best_random, fit_random = optim_random(Distances_cities, maxevals)
	md"La mejor solución con pruebas aleatorias da $(round(fit_random, digits=2)) y visualmente es:"
end

# ╔═╡ 9496e22b-913c-4d77-ba36-c3f2ada64a71
plot_sol(Position_cities, best_random, fit_random)

# ╔═╡ 00984827-fc5a-42b5-8073-5d6d7e3e4d54
md"""
!!! note
	¿Cómo os parece? ¿Razonable?

	Prueba a ajustar el número de evaluaciones y ver cómo cambia el fitness.
"""

# ╔═╡ 5bc1c907-f644-4070-9d69-cb27c7864a84
md"""
#### Vamos a ver cómo evoluciona de forma más interactiva.

Usa el _slider_ para adaptar la evaluación.
"""

# ╔═╡ b21b5893-36c8-4b30-aaa0-4570a200874f
begin
	slider = @bind evals_dynamic Slider(1:10_000, default=1)
	nothing
end

# ╔═╡ 8b7885ec-c853-432a-89c5-7221ba5eda03
begin
	local sol, fit
	seed!(169)
	sol, fit = optim_random(Distances_cities, evals_dynamic)
	TwoColumnWideRight(md"Evaluaciones: $(evals_dynamic) $br $slider", plot_sol(Position_cities, sol, fit))
end

# ╔═╡ d43f52c0-2b49-49f5-8f5f-139963384599
md"""
### Midiendo el rendimiento

Ahora vamos a medir cómo de rápido es el algoritmo. Para ello vamos a probar los tiempos con distinto número máximo de evaluaciones (_maxevals_) y ver cómo funciona.
"""

# ╔═╡ a0fe8446-788a-45d9-9a79-8417eba14755
begin
	# Recorro desde 1000 hasta 50000
	evals_time = collect(1_000:1000:50_000)
	local time_alg = Float64[]

	for evals in evals_time
		time = @elapsed optim_random(Distances_cities, evals)
		push!(time_alg, time)
	end

	plot(evals_time, time_alg, legend=false, title="Tiempo con Búsqueda Aleatoria", xlabel="Evaluaciones", ylabel="Tiempo")
end

# ╔═╡ da349ffa-0e14-470e-9841-8c385b23440c
md"""
¿Cómo crees que se incrementa el tiempo con las evaluaciones?
$(@bind como_increm PlutoUI.MultiCheckBox(["Lineal", "Exponencial"]))
""" |> question_box

# ╔═╡ 2442ec93-4707-42ab-81cb-5d2d68e1643f
if como_increm == ["Lineal"]
	PlutoTeachingTools.correct()
elseif !isempty(como_increm)
	keep_working()
end

# ╔═╡ 4488cb35-342e-418d-93b1-31359baa46e7
md"""
### Analizando la convergencia

Ahora vamos a analizar la convergencia, para ello vamos a guardar la mejor solución actual.
"""

# ╔═╡ fcfdcda5-377d-499f-a2bb-77fb72fe03ee
function optim_random_conv(distancias, maxevals, historic)
	n = size(distancias, 1)
	best = inicia_sol(n)
	best_fit = fitness(distancias, best)
	push!(historic, best_fit)
	evals = 1

	while evals < maxevals
		newsol = inicia_sol(n)
		fit_new = fitness(distancias, newsol)

		if fit_new < best_fit
			best = newsol
			best_fit = fit_new
		end
		evals += 1
		# Only change
		push!(historic, best_fit)
	end

	return best, best_fit
end

# ╔═╡ d086c073-9d82-4bfc-87f1-70631c4be183
begin
	local sol, fit, maxevals, historic
	seed!(169)
	maxevals = 50_000
	historic = Float32[]
	sol, fit = optim_random_conv(Distances_cities, maxevals, historic)
	plot(1:maxevals, historic, legend=false, title="Gráfica de convergencia", yaxis=:log, xlabel="EValuaciones", ylabel="Mejor Fitness")
end

# ╔═╡ 7499f1ae-c9e7-4426-9c47-efa150ef9f78
Foldable("Comentario", md"""
!!! note

	Como puedes ver, cada vez mejora menos.
""")

# ╔═╡ 3d6186cc-85b5-4539-a7d1-8ee3bf95056c
md"""
## Algoritmo Greedy

Vamos a aplicar el algoritmo Greedy, que recuerdo que se basa en ir construyendo una solución paso a paso, escogiendo en cada paso un criterio heurístico para elegir la mejor opción local, que puede no ser la mejor globalmente. 

En este problema es bastante intuitivo, la heurística será coger en cada ciudad la siguiente más cercana. 
"""

# ╔═╡ 9d9882ef-aab5-412e-837d-cc3decf51f7f
function greedy(distances)
	N = size(distances, 1)
	sol = zeros(Int, N)
	
	tam = 1
	# Primera aleatoria
	sol[tam] = rand(1:N)
	last = sol[tam]

	while tam < N
		# Miro las pendientes
		to_select = setdiff(1:N, sol)
		dist = -1
		mindist = Inf
		selected = 0
		
		for option in to_select
			dist = distances[sol[tam], option]

			if dist < mindist
				mindist = dist
				selected = option
			end
		end
		tam += 1
		sol[tam] = selected
	end
	
	return sol, fitness(distances, sol)
end

# ╔═╡ dee04e5c-41f5-437d-b2e6-bb3c125cbc40
begin
	sol_greedy, fit_greedy = greedy(Distances_cities)
	md"El greedy da un fitness de $(fit_greedy), ¿te parece competitivo?"
end

# ╔═╡ 8ee7b911-30de-4d5c-9752-49fa88b63e7f
md"Veamos la evolución"

# ╔═╡ e1c68742-621f-48a4-86e6-eda7d2989ae4
begin
	function plot_greedy(positions, distances, sol, tope)
		plt = plot_TSP(positions, Dict(:ms=>3, :color=>:gray))

		for i in 1:(tope-1)
			ant = sol[i]
			next = sol[i+1]
			plot!(plt, positions[1,[ant,next]],positions[2,[ant,next]], color=:black)
		end
	end
	
	anim = @animate for i ∈ 1:N
    plot_greedy(Position_cities, Distances_cities, sol_greedy, i)
	end
	gif(anim, "greedy.gif", fps = 1)
end

# ╔═╡ 4b6b92d3-a611-49c3-880c-f46fba0cecea
md"""
## Algoritmo de Búsqueda Local

En este caso vamos a aplicar el modelo de Búsqueda Local visto en clase, en particular el enfoque primero mejor.

Primero vamos a crear una solución aleatoria, y luego aplicamos un operador que cambie la solución un poco, la comparamos y nos quedamos la mejor de ambas, y luego se vuelve a aplicar lo mismo, hasta alcanzar un número de soluciones.
"""

# ╔═╡ f379ac50-dd36-40ed-b76d-2e5786f2ebc8
md"Definimos la función que muta:"

# ╔═╡ e2df8887-5ba4-430c-aad7-5243c2f137ed
function mutate(solution)
	result = copy(solution)
	N = length(solution)
	posi1 = rand(1:N)
	posi2 = rand(1:N)

	# Compruebo que sea diferente de la primera
	while posi2 == posi1
		posi2 = rand(1:N)
	end

	# Intercambio posiciones
	result[posi1] = solution[posi2]
	result[posi2] = solution[posi1]
	return result
end

# ╔═╡ b8f04454-777c-453e-9afa-4e28967c9bb7
md"Ahora definimos el método de Búsqueda Local. Para estudiar la convergencia vamos a guardar directamente las soluciones generadas."

# ╔═╡ 3dd5ed16-9e75-4419-8050-7a826b0f8dfa
function busquedaLocal(dist, maxevals=50_000, historic=nothing)
	current_sol = inicia_sol(size(dist, 1))
	current_fit = fitness(dist, current_sol)
	best_sol = copy(current_sol)
	best_fit = current_fit
	evals = 1
	if !isnothing(historic)
		push!(historic, (current_fit, best_fit))
	end
	
	while evals < maxevals
		current_sol = mutate(best_sol)
		current_fit = fitness(dist, current_sol)
		evals += 1

		if current_fit < best_fit
			best_fit = current_fit
			best_sol = current_sol
		end
		
		if !isnothing(historic)
			push!(historic, (current_fit, best_fit))
		end
	end
	
	return best_sol, best_fit
end

# ╔═╡ ee41d7e7-cc0e-4201-95c8-5a631423ec85
md"Se puede usar simplemente usando la función **busquedaLocal**"

# ╔═╡ 868f6a4f-1ab4-45eb-beb8-340183faf526
begin
	sol_ls, fit_ls = busquedaLocal(Distances_cities)
	"Fitness: $(fit_ls)"
end

# ╔═╡ c75a3c0a-8d68-4b20-a20b-914ad237972b
md"Vamos a probarlo con un slider"

# ╔═╡ 6628b477-f3f3-451f-81db-cd201a46b17b
begin
	slider_ls = @bind evals_ls Slider(1:50_000, default=1)
	nothing
end

# ╔═╡ 7faa1882-e5dc-4c55-ace5-c0007ed39de1
begin
	local sol, fit
	seed!(169)
	sol, fit = busquedaLocal(Distances_cities, evals_ls)
	TwoColumnWideRight(md"Evaluaciones: $evals_ls $br $slider_ls", plot_sol(Position_cities, sol, fit))
end

# ╔═╡ 2a077552-7ef0-4e53-bfbb-908ebee11d53
begin
function show_conv(method, distances)
	historic = Tuple{Float64,Float64}[]
	sol, fit = method(distances, evals_ls, historic)
	plt = plot(1:evals_ls, first.(historic), label="actual", size=(700, 400), xlabel="Evaluaciones", ylabel="Fitness", yscale=:log10)
	plot!(plt, 1:evals_ls, last.(historic), label="mejor")
end
md"""
### Gráfica de convergencia

Vamos a analizar la gráfica de convergencia, mostrando tanto el fitness de la mejor solución y la solución actual
"""
end

# ╔═╡ e7832961-cb91-4dfb-9b2e-e20e617568a6
show_conv(busquedaLocal, Distances_cities)

# ╔═╡ b662a059-b970-4aa4-9fd2-e5a27f0b047f
md"""
## Tabla comparativa

Vamos a medir los algoritmos con distintas evaluaciones y medir los tiempos.
"""

# ╔═╡ 64d92285-f7db-4fa2-ab12-d3b247ffd641
md"""
$(@bind evals_comp Slider(1:100_000, default=1))
"""

# ╔═╡ 46596778-9dbd-426c-a2a7-4014b8b2987c
begin
function times(distances)
	df = DataFrame(name=String[], tiempos=Float32[], best=Float32[])
	seed!(169)

	time_greedy = @elapsed _, fit_greedy = greedy(distances)
	push!(df, (name="Greedy", tiempos=time_greedy, best=fit_greedy))
	seed!(169)
	time_random = @elapsed _, fit_random = optim_random(distances, evals_comp)
	push!(df, (name="Random", tiempos=time_random, best=fit_random))
	seed!(169)
	time_BL = @elapsed _, fit_BL = busquedaLocal(distances, evals_comp)
	push!(df, (name="Búsqueda Local", tiempos=time_BL, best=fit_BL))
	
	PrettyTables.pretty_table(HTML, df, header=["Algoritmo", "Tiempo", "Mejor Fit."], title="Resultado con $(evals_comp) evaluaciones", formatters = (PrettyTables.ft_printf("%.3e", [2]),PrettyTables.ft_printf("%2.3f", [3])))
end
	times(Distances_cities)
end

# ╔═╡ 086a03d5-aced-4ed5-a250-21ef3c51caeb
PlutoTeachingTools.Foldable(
	"Preguntas", 
	question_box(md"""
	¿Qué te parecen los resultados? Indica lo que te parece correcto:

	$(@bind pregunta PlutoUI.MultiCheckBox(["T" => "La búsqueda local mejora a la aleatoria", "F" => "La búsqueda local no mejora a la aleatoria"]))
	"""
	)
)

# ╔═╡ 6c85c8c1-8758-42ee-99a4-bfb81c70a966
begin
	if !isempty(pregunta) && ("F" in pregunta || length(pregunta)<1)
		keep_working()
	elseif !isempty(pregunta)
		correct()
	end
end

# ╔═╡ Cell order:
# ╟─5ccf83de-10cd-46e0-b940-664b67831e48
# ╟─0e1d1860-943a-4808-834f-833e15bc0396
# ╟─f78d4556-c30e-11ed-3cc3-ffa49c1c0da9
# ╟─63967850-2682-4d70-89cf-76d91d5da628
# ╟─8ff8d174-7651-493a-94ba-c613fd7ff69b
# ╟─4b016a19-3e60-429c-a52b-9a7415bbb808
# ╟─d09d69b4-16b6-4bc4-ac73-209d4599fcce
# ╟─13528697-092b-43f8-b6e3-12e4cbc12559
# ╟─37c8cf4b-eed8-428f-b181-36727af9d472
# ╟─dbb838ef-262a-4db4-8bae-5e8332fba3a6
# ╠═02fcaf7d-7fe5-48f6-83ba-5387e342892d
# ╟─d80dd12d-c9d8-4dc1-b42d-ecb746b98101
# ╟─80eef61f-1414-4aeb-86de-416263797d29
# ╟─3315e650-cf41-4bd9-96f1-e548a19f7f44
# ╟─251fbc45-c637-4652-ad50-01d40ce2537c
# ╟─88d163e8-1f21-48a4-9ae6-2bb217b7cff3
# ╟─66183a3b-11e7-4c92-8784-714b5d22738e
# ╟─0daabc72-3ef2-488d-8f6e-aefd2cae841d
# ╠═f6d62ede-1e5e-41e1-9981-909f070d63fb
# ╟─9aa54296-488d-4808-b457-a64ab8fd566c
# ╠═2be1750b-85d5-4b98-a4f0-4148285cb058
# ╟─668baf12-9a75-4ec6-903e-236ab69066a5
# ╠═1792f776-9916-402f-9de3-5716ed6744e9
# ╟─ec6be0aa-e367-49cf-a3d4-cfc1e69602e0
# ╟─87f6103e-be1f-404b-ab36-7ae68231ebed
# ╟─efdb8e91-8c36-4990-a18a-be37572de341
# ╠═55c3e565-c98d-4235-a503-2a3fc6f2ef9a
# ╟─498c1ce3-ef85-4472-b568-d7f95710c1f5
# ╟─b810106c-6b18-4670-94e9-976cf56c2ab5
# ╟─a0ea972b-1cbf-4f52-a6cc-20f0a66700b2
# ╟─8fb74b55-4a82-4eb7-bdcf-d63fa4cf3be4
# ╟─9496e22b-913c-4d77-ba36-c3f2ada64a71
# ╟─00984827-fc5a-42b5-8073-5d6d7e3e4d54
# ╟─5bc1c907-f644-4070-9d69-cb27c7864a84
# ╟─b21b5893-36c8-4b30-aaa0-4570a200874f
# ╟─8b7885ec-c853-432a-89c5-7221ba5eda03
# ╟─d43f52c0-2b49-49f5-8f5f-139963384599
# ╠═a0fe8446-788a-45d9-9a79-8417eba14755
# ╟─da349ffa-0e14-470e-9841-8c385b23440c
# ╟─2442ec93-4707-42ab-81cb-5d2d68e1643f
# ╟─4488cb35-342e-418d-93b1-31359baa46e7
# ╠═fcfdcda5-377d-499f-a2bb-77fb72fe03ee
# ╠═d086c073-9d82-4bfc-87f1-70631c4be183
# ╟─7499f1ae-c9e7-4426-9c47-efa150ef9f78
# ╟─3d6186cc-85b5-4539-a7d1-8ee3bf95056c
# ╠═9d9882ef-aab5-412e-837d-cc3decf51f7f
# ╠═dee04e5c-41f5-437d-b2e6-bb3c125cbc40
# ╟─8ee7b911-30de-4d5c-9752-49fa88b63e7f
# ╟─e1c68742-621f-48a4-86e6-eda7d2989ae4
# ╟─4b6b92d3-a611-49c3-880c-f46fba0cecea
# ╟─f379ac50-dd36-40ed-b76d-2e5786f2ebc8
# ╠═e2df8887-5ba4-430c-aad7-5243c2f137ed
# ╟─b8f04454-777c-453e-9afa-4e28967c9bb7
# ╠═3dd5ed16-9e75-4419-8050-7a826b0f8dfa
# ╟─ee41d7e7-cc0e-4201-95c8-5a631423ec85
# ╟─868f6a4f-1ab4-45eb-beb8-340183faf526
# ╟─c75a3c0a-8d68-4b20-a20b-914ad237972b
# ╟─6628b477-f3f3-451f-81db-cd201a46b17b
# ╟─7faa1882-e5dc-4c55-ace5-c0007ed39de1
# ╟─2a077552-7ef0-4e53-bfbb-908ebee11d53
# ╟─e7832961-cb91-4dfb-9b2e-e20e617568a6
# ╟─b662a059-b970-4aa4-9fd2-e5a27f0b047f
# ╟─64d92285-f7db-4fa2-ab12-d3b247ffd641
# ╟─46596778-9dbd-426c-a2a7-4014b8b2987c
# ╟─086a03d5-aced-4ed5-a250-21ef3c51caeb
# ╟─6c85c8c1-8758-42ee-99a4-bfb81c70a966
