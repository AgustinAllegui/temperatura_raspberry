% [u] = funcion(Ts, t, ref0, temp1, [futRef], [ph])

function [u] = histeresis(Ts, t, ref0, temp)
  
%  global limite;
%  if(isempty(limite))
%    limite = 5;
%  end

  limite = 5;
  
%  disp("prueba desde octave");

  u = 0;
  
  if(limite>0)
    if(temp>ref0+limite)
      u = 0;
      limite = -limite;
    else
      u = 100;
    end
  else
    if(temp<ref0+limite)
      u = 100;
      limite = -limite;
    else
      u = 0;
    end
  end

  

endfunction 