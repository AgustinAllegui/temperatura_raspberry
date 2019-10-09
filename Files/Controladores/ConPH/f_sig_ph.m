function u = f_sig_ph(Ts, t, ref0, temp, futureRef, ph)

%  display(futureRef);
  
  u = ph + ref0 - futureRef(length(futureRef));

end