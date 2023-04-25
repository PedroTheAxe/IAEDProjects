--1. Qual o local publico onde estao registadas menos anomalias? VERIFICADA

select nome,count(*) from local_publico
natural join item it
join incidencia i on it.id=i.item_id
group by nome
having count(*) <= all(select count(*)
from local_publico
natural join item it
join incidencia i on it.id=i.item_id
group by nome);


--2. Qual o local publico com mais anomalias de traducao no 1º semestre de 2020?


select distinct nome,count(*) from local_publico
natural join item it
join incidencia i on i.item_id=it.id
join anomalia a on i.anomalia_id=a.id
join anomalia_traducao atd on a.id=atd.id
where ts between '2020-01-01 00:00:00' and '2020-06-30 23:59:59'
group by nome
having count(*) >= all(select count(*)
from local_publico
natural join item it
join incidencia i on i.item_id=it.id
join anomalia a on i.anomalia_id=a.id
join anomalia_traducao atd on a.id=atd.id
where ts between '2020-01-01 00:00:00' and '2020-06-30 23:59:59'
group by nome);


--3. Quais sao os utilizadores que registaram em 2020 propostas de correcao em todos os locais
--publicos situados a sul de Rio Maior (Portugal)?

select distinct email from proposta_de_correcao p
where not exists (
    select it.id
    from item it
    join incidencia i on it.id=i.item_id
    where it.latitude < 39.336775
    except
    select inc.item_id
    from incidencia inc
    where p.email = inc.email)
and p.data_hora between '2020-01-01 00:00:00' and '2020-12-31 23:59:59';

--4. Quais sao os utilizadores que apresentaram propostas de correcao para todas anomalias por eles
--registadas no ano de 2020?

select distinct email from correcao c
where not exists(
    select i.email
    from incidencia i join anomalia a on a.id=i.anomalia_id
    where a.ts between '2020-01-01 00:00:00' and '2020-12-31 23:59:59'
    except
    select c2.email
    from correcao c2
    join  incidencia i2 on i2.anomalia_id=c2.anomalia_id
    where c2.email = c.email);

