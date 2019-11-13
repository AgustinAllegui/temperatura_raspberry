% [u] = funcion(Ts, t, ref0, temp1, [futRef], [ph])

function u = UisR_fut(Ts, t, ref0, temp1, futRef)

  futRef = futRef(:);
  u = futRef(length(futRef));

endfunction