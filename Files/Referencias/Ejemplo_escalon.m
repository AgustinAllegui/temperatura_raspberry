% Ejemplo_escalon.m
% Escalon de 120 grados en el segundo 20.

% ref [?C] = referencia en el instante t
% t [segundos] = tiempo desde el inicio del experimento 
% Ts [segundos] = tiempo de muestreo

function ref = Ejemplo_escalon(Ts, t)
  if t<20
    ref = 0;
  else
    ref = 120;
  end
end
