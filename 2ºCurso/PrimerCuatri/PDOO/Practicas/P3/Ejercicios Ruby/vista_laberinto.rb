require_relative 'controlador_laberinto/controlador'

class VistaLaberinto

    def initialize(controlador)
        @controlador=controlador
    end

    def menu_usuario()

        estado=@controlador.estado
        values=[*1..10].map!(&:to_s)
        case estado
            when Estado_juego::EN_ENTRADA_LABERINTO
                puts "Intoduzca el número de vidas (entre 1 y 10) antes de entrar en el laberinto"
                st=gets.chomp
                while (!values.include? st)
                    puts "Intoduzca el número de vidas (entre 1 y 10) antes de entrar en el laberinto"
                    st=gets.chomp
                end
                @controlador.entrar(st.to_i)
                puts "El jugador ha entrado en el laberinto"

            when Estado_juego::DENTRO_VIVO
                    puts informe_dentro(@controlador.habitacion_usuario,@controlador.vidas)
                    puts "Pulse una tecla para continuar"
                    st= gets.chomp
                    movimiento=@controlador.intentar_avanzar()
                    puts "El jugador se mueve al " + Lista_direcciones[movimiento]
            when Estado_juego::EN_SALIDA_LABERINTO
                puts informe_final(@controlador.vidas())
                exit 0

            when Estado_juego::DENTRO_MUERTO
                puts informe_final(@controlador.vidas())
                exit 0
            end

        menu_usuario
    end

    def informe_dentro(habitacion, vidas)
        puts "El jugador tiene #{vidas} vidas"
        puts "El usuario se encuentra en la #{habitacion}"
    end
    def informe_final(vidas)
        habitacion=@controlador.habitacion_usuario()
        if(vidas>0)
            puts "El jugador ha ganado con #{vidas} vidas :)"
        else
            puts "El jugador ha perdido :("
        end
    end
end