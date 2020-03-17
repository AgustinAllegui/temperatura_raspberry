% Histéresis.m
% control SI NO con histeresis.
% limite superior 200 °C
% limite inferior 150 °C

% u [%] = accion de control
% Ts [segundos] = tiempo de muestreo
% t [segundos] = tiempo desde el inicio
% ref0 [ºC] = referencia en el instante actual
% temp [ºC] = temperatura medida


function [u] = histeresis(Ts, t, ref0, temp)
  
  limite_inferior = 150;
  limite_superior = 200;

  % inicializacion de variable limite_actual
  global limite_actual;
  if(isempty(limite_actual))
    limite_actual = limite_superior;
  end

  if (limite_actual == limite_superior)
  
    % cuando supera el limite superior, apagar actuador y cambiar el limite
    if (temp > limite_actual)
      u = 0;
      limite_actual = limite_inferior;
    else
      u = 100;
    end
  else
    % cuando baja del limite inferior, activar actuador  y cambiar el limite
    if (temp < limite_actual)
      u = 100;
      limite_actual = limite_superior;
    else
      u = 0;
    end
  end
end
