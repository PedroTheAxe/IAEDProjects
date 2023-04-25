select tipo_anomalia, lingua, dia_da_semana,count(*)
from f_anomalia
    natural join d_lingua
    natural join d_tempo
group by tipo_anomalia, lingua, dia_da_semana
union
select tipo_anomalia, lingua, null,count(*)
from f_anomalia
    natural join d_lingua
    natural join d_tempo
group by tipo_anomalia, lingua
union
select null, lingua, dia_da_semana,count(*)
from f_anomalia
    natural join d_lingua
    natural join d_tempo
group by lingua, dia_da_semana
union
select tipo_anomalia, null, dia_da_semana,count(*)
from f_anomalia
    natural join d_lingua
    natural join d_tempo
group by tipo_anomalia, dia_da_semana
union
select tipo_anomalia, null, null,count(*)
from f_anomalia
    natural join d_lingua
    natural join d_tempo
group by tipo_anomalia
union
select null, lingua, null,count(*)
from f_anomalia
    natural join d_lingua
    natural join d_tempo
group by lingua
union
select null, null, dia_da_semana,count(*)
from f_anomalia
    natural join d_lingua
    natural join d_tempo
group by dia_da_semana
union
select null, null, null,count(*)
from f_anomalia
    natural join d_lingua
    natural join d_tempo;