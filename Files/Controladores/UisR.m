% UisR.m
% la accion de control es numericamente igual a la referencia.
% (util para modelado)

% u [%] = accion de control
% Ts [segundos] = tiempo de muestreo
% t [segundos] = tiempo desde el inicio
% ref0 [ºC] = referencia en el instante actual
% temp [ºC] = temperatura medida

function u = UisR(Ts, t, ref0, temp)
  
  u = ref0;

end
