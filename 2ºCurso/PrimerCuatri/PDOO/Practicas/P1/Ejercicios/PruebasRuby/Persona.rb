class Persona
  #atributo y metodo de clase
  @@num_personas = 0
  def self.num_personas
    @@num_personas
  end
  #inicializador
  def initialize (un_nombre)
    #atributo de instancia
    @nombre = un_nombre
    @@num_personas += 1
  end

  def get_numPersonas()
    return @@num_personas
  end
end