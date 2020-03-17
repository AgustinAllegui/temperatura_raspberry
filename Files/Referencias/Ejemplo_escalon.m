% referencia1.m
% Escalon de 120 grados en el segundo 20.

% ref [ºC] = referencia en el instante t
% t [segundos] = tiempo desde el inicio del experimento 
% Ts [segundos] = tiempo de muestreo

function ref = referencia1(Ts, t)
  if t<20
    ref = 0;
  else
    ref = 120;
  end
end
