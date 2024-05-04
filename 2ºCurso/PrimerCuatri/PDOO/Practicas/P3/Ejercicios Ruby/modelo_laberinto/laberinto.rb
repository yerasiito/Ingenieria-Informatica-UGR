# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative "habitacion.rb"
require_relative "elemento_separador.rb"


module Modelo_laberinto
  

class Laberinto
  
  attr_reader :puerta_entrada, :puerta_salida, :habitaciones
  
  def initialize
     @puerta_entrada=nil
     @puerta_salida=nil
    crear_habitaciones
    add_paredes
    add_puertas
  end
  
  def crear_habitaciones
    @habitaciones=Array.new(3)
    3.times do |index|
      @habitaciones[index]=Habitacion.new(index+1)
     for direccion in 0..3
        @habitaciones[index].set_lado(direccion, nil)
      end
    end
  end
  
  def add_paredes
    # hab 1
    pared=Elemento_separador.nueva_pared(@habitaciones[0], nil)
    @habitaciones[0].set_lado(Direccion::NORTE, pared)
    pared=Elemento_separador.nueva_pared(@habitaciones[0], nil)
    @habitaciones[0].set_lado(Direccion::OESTE, pared)
    
    # hab 2
     pared=Elemento_separador.nueva_pared(@habitaciones[1], nil)
    @habitaciones[1].set_lado(Direccion::NORTE, pared)
    pared=Elemento_separador.nueva_pared(@habitaciones[1], nil)
    @habitaciones[1].set_lado(Direccion::SUR, pared)
    
    # hab 3
     pared=Elemento_separador.nueva_pared(@habitaciones[2], nil)
    @habitaciones[2].set_lado(Direccion::ESTE, pared)
    pared=Elemento_separador.nueva_pared(@habitaciones[2], nil)
    @habitaciones[2].set_lado(Direccion::SUR, pared)
    
  end
  
  def add_puertas
    # puertas interiores
    puerta=Elemento_separador.nueva_puerta(@habitaciones[0], @habitaciones[1])
    @habitaciones[0].set_lado(Direccion::ESTE, puerta)
    @habitaciones[1].set_lado(Direccion::OESTE, puerta)
    
    puerta=Elemento_separador.nueva_puerta(@habitaciones[1], @habitaciones[2])
    @habitaciones[1].set_lado(Direccion::ESTE, puerta)
    @habitaciones[2].set_lado(Direccion::OESTE, puerta)
    
    # puertas exteriores
    @puerta_entrada=Elemento_separador.nueva_puerta(@habitaciones[0], nil)
    @habitaciones[0].set_lado(Direccion::SUR, @puerta_entrada)
    
     @puerta_salida=Elemento_separador.nueva_puerta(@habitaciones[2], nil)
     @habitaciones[2].set_lado(Direccion::NORTE, @puerta_salida)

    
  end
  
  def to_s
   s= "Habitaciones del laberinto:\n"
   s=s+@habitaciones.join

    
    end
  end
    

end

# def prueba
#  lab=Laberinto.new()
#  puts lab
# end

# prueba