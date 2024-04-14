; Datos de personas

(deftemplate Persona
	(field Nombre)
	(field Edad)
	(field Sexo)
	(field EstadoCivil)
)

(deffacts VariosHechos
	(Persona
	(Nombre JuanCarlos)
	(Edad 33)
)

(Persona
	(Nombre Maria)
	(Sexo M))
)

(deffacts OtrosHechos
	(NumeroDeReactores 4)
) 