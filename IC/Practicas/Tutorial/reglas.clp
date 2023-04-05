(deffacts VariosHechosVectores
	(Persona Pedro 45 V SI)
	(Persona Maria 34 M NO)
)

(defrule ECivilPedro_Soltero
	(Persona Pedro 45 V NO)
	=>
	(printout t "Pedro está bien soltero" crlf))

(defrule ECivilPedro_Casado
	(Persona Pedro 45 V SI)
	=>
	(printout t "Pedro está casado y deprimido" crlf))

(defrule ECivilMaria_Soltera
	(Persona Maria 34 M NO)
	=>
	(printout t "Maria esta solterona" crlf))