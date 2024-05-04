require_relative "../modelo_laberinto/tipo_separacion"
require_relative 'Estado_juego'
require_relative '../modelo_laberinto/direccion'

class Controlador
    attr_reader :estado, :vidas, :habitacion
    attr_reader :habitacion_usuario, :laberinto

    def initialize(modelo)
      @habitacion_usuario=nil
      @laberinto=modelo
      @estado=Estado_juego::EN_ENTRADA_LABERINTO
      @vidas=0
    end
    def entrar(vidas)
      @estado=Estado_juego::DENTRO_VIVO
      @habitacion_usuario=laberinto.puerta_entrada.habitacion_al_otro_lado(nil)
      pared=Elemento_separador.nueva_pared(@habitacion_usuario, nil)
      @habitacion_usuario.set_lado(Direccion::SUR, pared)
      @vidas=vidas
    end
    def intentar_avanzar()
      direccion=rand(0..3)
      if (@habitacion_usuario.pasar(direccion))
        @habitacion_usuario= @habitacion_usuario.get_lado(direccion).habitacion_al_otro_lado(@habitacion_usuario)
        if (@habitacion_usuario == nil)
          @estado=Estado_juego::EN_SALIDA_LABERINTO
          @estado=Estado_juego::EN_SALIDA_LABERINTO
        else
          pared=Elemento_separador.nueva_pared(@habitacion_usuario, nil)
          @habitacion_usuario.set_lado((direccion+1)%4,pared)
        end
      else
        @vidas= @vidas-1
        if(@vidas==0)
          @estado=Estado_juego::DENTRO_MUERTO
        end
      end
      direccion

    end
end
