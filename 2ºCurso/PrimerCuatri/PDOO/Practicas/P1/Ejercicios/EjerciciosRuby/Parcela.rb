class Parcela
  #Variables de clase
  # @@FACTORALQUILERCALLE = 1.0
  # @@FACTORALQUILERCASA = 1.0
  # @@FACTORALQUILERHOTEL = 4.0
  @FACTORALQUILERCALLE = 1.0
  @FACTORALQUILERCASA = 1.0
  @FACTORALQUILERHOTEL = 4.0
  def self.factor_alquiler_calle
    return @FACTORALQUILERCALLE
  end

  def self.factor_alquiler_casa
    return @FACTORALQUILERCASA
  end

  def self.factor_alquiler_hotel
    return @FACTORALQUILERHOTEL
  end

  def initialize(n, p_compra, p_edificar, p_base_alquiler) #constructor
    @nombre = n
    @precio_compra = p_compra
    @precio_edificar = p_edificar
    @precio_base_alquiler = p_base_alquiler
    @numCasas = 0
    @numHoteles = 0
  end

  public
  def Detalles #Imprime los datos de la clase
    puts "Nombre de la parcela: #@nombre"
    puts "Precio de compra: #@precio_compra"
    puts "Precio de edificación: #@precio_edificar"
    puts "Precio base de alquiler: #@precio_base_alquiler"
    puts "Numero de casas: #@numCasas"
    puts "Numero de Hoteles: #@numHoteles"
    puts "El Precio total a pagar es: #{get_precio_alquiler_completo}\n\n"
  end
  #Metodos get de las variables de la clase
  attr_reader :nombre
  attr_reader :precio_compra
  attr_reader :precio_edificar
  attr_reader :precio_base_alquiler

  def get_precio_alquiler_completo
    return @precio_base_alquiler * (Parcela.factor_alquiler_calle +
                                   @numCasas * Parcela.factor_alquiler_casa +
                                   @numHoteles * Parcela.factor_alquiler_hotel)
  end

  #2 metodos bool que aumentan en 1 la construccion designada
  def construir_casa?
    @numCasas+=1
    return true
  end
  def construir_hotel?
    @numHoteles+=1
    return true
  end
end