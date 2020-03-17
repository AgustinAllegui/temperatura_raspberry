% UisR_fut.m
% la accion de control es numericamente igual a la referencia mas
% futura disponible.

% u [%] = accion de control
% Ts [segundos] = tiempo de muestreo
% t [segundos] = tiempo desde el inicio
% ref0 [ºC] = referencia en el instante actual
% temp [ºC] = temperatura medida
% futRef [ºC] = vector con referencias futuras
%  [futRef(1)  = referencia en proximo tiempo de muestreo
%   futRef(2)  = referencia dentro de 2 tiempos de muestreo
%   ...
%   futRef(n)]  = referencia dentro de n tiempos de muestreo

function u = UisR_fut(Ts, t, ref0, temp1, futRef)

  futRef = futRef(:);
  u = futRef(length(futRef));

end
