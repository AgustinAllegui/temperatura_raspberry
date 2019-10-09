% [u] = funcion(Ts, t, ref0, temp1, [futRef], [ph])

function u = f_siguiente(Ts, t, ref0, temp1, futRef)
  
  display(Ts);
  display(t);
  display(ref0);
  display(temp1);
  display(futRef);
  
  
  diferencia = futRef(1) - ref0;
  u = diferencia;

end