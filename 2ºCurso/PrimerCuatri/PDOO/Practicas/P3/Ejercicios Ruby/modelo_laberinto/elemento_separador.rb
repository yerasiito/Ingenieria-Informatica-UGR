# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative "tipo_separacion.rb"
require_relative "habitacion.rb"


module Modelo_laberinto
  

class Elemento_separador
  
  attr_reader :tipo, :hab1, :hab2
  
  def initialize (tipo, hab1, hab2)
    @tipo=tipo
    @hab1=hab1
    @hab2=hab2
  end
  
  private_class_method :new
  
  def self.nueva_puerta (hab1, hab2)
    new(Tipo_separacion::PUERTA, hab1, hab2)
  end
  
  def self.nueva_pared (hab1, hab2)
    new(Tipo_separacion::PARED, hab1, hab2)
  end
  
  def habitacion_al_otro_lado(hab)
    if @hab1==hab
      then return @hab2
    else return @hab1
    end
  end
  
  def pasar
    @tipo==Tipo_separacion::PUERTA
  end

  def to_s
    if @tipo==Tipo_separacion::PUERTA
      if @hab2!=nil
        st="Soy una puerta entre "+@hab1.num_habitacion.to_s+" y "+@hab2.num_habitacion.to_s
      else        
        st="Soy una puerta de "+@hab1.num_habitacion.to_s+" al exterior"
      end
    else
      if @hab2!=nil
      st="Soy una pared entre "+@hab1.num_habitacion.to_s+" y "+@hab2.num_habitacion.to_s
      else
          st="Soy una pared entre la "+@hab1.num_habitacion.to_s+" y el exterior"
    end
  end
  
  end
end

end
  
### pruebas ####

include Modelo_laberinto

def pruebas
  
  
  puts "clase:"+Tipo_separacion::PARED.class.to_s
  # puts "primer tipo: "+Lista_Tipo_separacion[Tipo_separacion::PARED].to_s
  # puts "segundo tipo: "+Lista_Tipo_separacion[Tipo_separacion::PUERTA].to_s

  hab1=Habitacion.new(1)
  hab2=Habitacion.new(2)
  hab3=Habitacion.new(3)
  puerta=Elemento_separador.nueva_puerta(hab1, hab2)
  puts "puerta:"+puerta.to_s
  pared=Elemento_separador.nueva_pared(hab2, hab3)

  
  
end



pruebas

