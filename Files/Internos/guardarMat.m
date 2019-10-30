% guardar un archivo .mat

% Tiempo, Referencia, Temperatura, U, PH

function ok = guardarMat(phFlag)
  ok = 0;
  
  largo = 0;
  
  [filepath,name,ext] = fileparts(mfilename('fullpathext'));
  
  run([filepath '/setDirIn.m']);
  run([filepath '/setDirOut.m']);
  
  m_file = fopen(dirIn);
  m_datos = textscan(m_file, '%n %n %n %n %n');
  
  ensayo.tiempo = m_datos{1}(:,1);
  largo = length(ensayo.tiempo);
  
  ensayo.referencia = m_datos{2}(:,1);
  largo = min(largo, length(ensayo.referencia));
  
  ensayo.temperatura = m_datos{3}(:,1);
  largo = min(largo, length(ensayo.temperatura));
  
  ensayo.u = m_datos{4}(:,1);
  largo = min(largo, length(ensayo.u));
  
  if (phFlag == 1)
    ensayo.ph = m_datos{5}(:,1);
    largo = min(largo, length(ensayo.ph));
  endif
  
  ensayo.tiempo = ensayo.tiempo(1:largo);
  ensayo.referencia = ensayo.referencia(1:largo);
  ensayo.temperatura = ensayo.temperatura(1:largo);
  ensayo.u = ensayo.u(1:largo);
  if (phFlag == 1)
    ensayo.tiempo = ensayo.tiempo(1:largo);
  endif
  
  ensayo.ts = ensayo.tiempo(2)-ensayo.tiempo(1);
  
  save(dirOut, 'ensayo');
  
  
endfunction