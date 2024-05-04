# encoding:utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.


class Vista2_laberinto
  
  @@DENTRO=true
  @@VIVO=true
 
  def initialize (controlador, modelo)
    @controlador=controlador
    @modelo=modelo
    @movimiento=-1
  end
      
   
  
  def menu_usuario()
    
    estado=@controlador.estado
    values=[*1..10].map!(&:to_s)
   
    case estado
    when Estado_juego::EN_ENTRADA_LABERINTO
     
      puts laberinto(!@@DENTRO, @@VIVO) # dentro y vivo
       puts usuario_en_entrada
     
     
      puts "Intoduzca el número de vidas (entre 1 y 10) antes de entrar en el laberinto"
      st=gets.chomp
     
      while (!values.include? st)
        puts "Intoduzca el número de vidas (entre 1 y 10) antes de entrar en el laberinto"
        st=gets.chomp
      end
      @controlador.entrar(st.to_i)
     
     
    when Estado_juego::DENTRO_VIVO
      puts laberinto(true, true)
 
      puts "Pulse una tecla"
      st= gets.chomp
      @movimiento=@controlador.intentar_avanzar()
      
      
    when Estado_juego::EN_SALIDA_LABERINTO
      puts usuario_en_salida
      puts laberinto(false, true)
      exit 0
      
    when Estado_juego::DENTRO_MUERTO
      puts laberinto(true, false)
      exit 0
    end
    menu_usuario
  def usuario_muerto
    "☻"
  end

      _usuario
  end
  def usuario_muerto
    "☻"
  end


  def usuario_muerto
    "☻"
  end


  
  def vidas(total_vidas)
    st=""
    total_vidas.times{ st=st+"♥"}
    st
  end

  def direccion(r)
  d=Array["↑","↓","→","←"]
return d[r]
  end
  
  def usuario_vivo
    "☺"
  
  end
  
  def usuario_muerto
    "☻"
  end
  
      
  def habitacion_vacia()
    " "
  end
  
  def usuario_fuera(puerta)
      st=""
      pos=puerta.habitacion_al_otro_lado(nil).num_habitacion
      (pos-1).times{
        st=st+"    "
      }
      st=st+"  "+usuario_vivo+"\n" 
    end 
  
  def usuario_en_salida
     
     usuario_fuera(@modelo.puerta_salida)
  end
  
  def usuario_en_entrada
     usuario_fuera(@modelo.puerta_entrada)
    
  end
  
  def usuario (dentro, vivo)
    if (dentro)
      usuario=usuario_vivo
      if !vivo 
        usuario=usuario_muerto
      end
    else usuario=habitacion_vacia()
    end
    usuario
  end


  
  
  
    def puerta()
      " "
    end
  
    def pared(vertical)
      if (vertical)
        "║"
      else
        "═"
      end
    end
      
  
   
    def extremo_laberinto(puerta)
      st=""
      pos=puerta.habitacion_al_otro_lado(nil).num_habitacion
      (pos-1).times{
        st=st+"    "
      }
      st=st+"  ▲\n" 
    end 
  
   
      
    def fachada_norte () 
      st=extremo_laberinto (@modelo.puerta_salida)
      st=st+"╔═";
      for hab in @modelo.habitaciones
        sep=hab.get_lado(Direccion::NORTE)
        if (sep!=nil && sep.tipo==Tipo_separacion::PUERTA)
          st=st+puerta
        else
          st=st+pared(false)
        end
        if (hab==@modelo.habitaciones.last)
          st=st+"═╗\n"
        else
          st=st+"═╦═"
        end
      end
      st
    end
  
    def fachada_sur (vidas)
   
      st="╚═";
      for hab in @modelo.habitaciones
        sep=hab.get_lado(Direccion::SUR)
        if (sep!=nil && sep.tipo==Tipo_separacion::PUERTA)
          st=st+puerta
        else
          st=st+pared(false)
        end
        if (hab==@modelo.habitaciones.last)
          st=st+"═╝"+"\n" + vidas(vidas)+"\n"
        else
          st=st+"═╩═"
        end
      end             
      st=st+extremo_laberinto(@modelo.puerta_entrada)
      st
    end
  
    def interior_habitaciones(usuario)
      st=""
      for hab in @modelo.habitaciones
        sep=hab.get_lado(Direccion::OESTE)
        if (sep!=nil && sep.tipo==Tipo_separacion::PUERTA)
          st=st+puerta
        else
          st=st+pared(true)
        end
        if (@controlador.habitacion_usuario==hab) 
          st=st+" "+usuario+" "
        else
          st=st+"   "
        end
      end
      st=st+pared(true)+" "+direccion(@movimiento)+"\n"
      st
    end
 
   def laberinto(dentro, vivo)
   st=fachada_norte()
   st=st+interior_habitaciones(usuario(dentro, vivo))
   st=st+fachada_sur(@controlador.vidas)
   end
  
  end

