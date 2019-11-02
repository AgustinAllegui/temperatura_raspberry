function [u] = PID_rbp(Ts, t, ref, temp, Kp, Ki, Kd)
%  u[%] = accion1 =  (kp*e(n) + Kd*(e(n)-e(n-1))/Ts + Ki * Ts * sumatoria(e);

  global error1;
  if(isempty(error1))
    error1 = 0;
  end

%  display("valores:");
%  display(Ts);
%  display(t);
%  display(ref);
%  display(temp);
%  display(Kp);
%  display(Ki);
%  display(Kd);

  global errorSum;
  if(isempty(errorSum))
    errorSum = 0;
  end

  error0 = ref-temp;
  errorSum = errorSum + error0;

  proporcional = Kp*error0;
  integral = Ki*Ts*errorSum;
  derivativo = Kd * (error0 - error1)/Ts;

  u = proporcional + integral + derivativo;

  error1 = error0;

end