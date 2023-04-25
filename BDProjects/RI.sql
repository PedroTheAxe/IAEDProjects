
-----------------------------RI-1, RI-2-----------------------------------------
drop trigger if exists anomalia_traducao_bit on anomalia_traducao;

create or replace function anomalia_traducao_bif()
    returns trigger as
$$
    declare newx1 decimal default 0;
            newy1 decimal default 0;
            newx2 decimal default 0;
            newy2 decimal default 0;
            oldx1 decimal default 0;
            oldy1 decimal default 0;
            oldx2 decimal default 0;
            oldy2 decimal default 0;
            old   text[];
            coortostr text[];

    begin
        if new.id in (select id from anomalia) then
            coortostr = regexp_split_to_array(new.zona2,',');
            newx1=cast(coortostr[1] as decimal);
            newy1=cast(coortostr[2] as decimal);
            newx2=cast(coortostr[3] as decimal);
            newy2=cast(coortostr[4] as decimal);

            Select (regexp_split_to_array(zona,',')) into old
            from anomalia
            where new.id=id;

            oldx1=cast(old[1] as decimal);
            oldy1=cast(old[2] as decimal);
            oldx2=cast(old[3] as decimal);
            oldy2=cast(old[4] as decimal);

            if new.lingua2 <> (select lingua from anomalia where new.id = id) and
               not ((newx1 < oldx2 and newx2 > oldx2) or (newx2 > oldx1 and newx1 < oldx1)
                or (newy1 < oldy2 and newy2 > oldy2) or (newy2 > oldy1 and newy1 < oldy1)) then
                return new;
            end if;
        end if;
    end;

$$ language plpgsql;

create trigger anomalia_traducao_bit
before insert on anomalia_traducao
for each row execute procedure anomalia_traducao_bif();

-----------------------------RI-4,5,6-----------------------------------------
drop trigger if exists utilizador_bit on utilizador;

create or replace function utilizador_bif()
	returns trigger as

$$
	begin
            raise Exception 'Nao foi possivel inserir o utilizador';
    end;
$$ language plpgsql;

create trigger utilizador_bit
before insert on utilizador
for each row execute procedure utilizador_bif();



drop function utilizador_qualificado_insert(emaill varchar(80), password varchar(20));

create or replace function utilizador_qualificado_insert(emaill varchar(80), password varchar(20))
	returns void as

$$
	begin
	        if emaill not in (select email from utilizador_regular) then
                alter table utilizador disable trigger utilizador_bit;
			    insert into utilizador values(emaill, password);
			    insert into utilizador_qualificado values(emaill);
                alter table utilizador enable trigger utilizador_bit;
			else
	            raise exception 'Este utilizador ja e regular';
	        end if;

	end;
$$ language plpgsql;

drop function utilizador_regular_insert(emaill varchar(80), password varchar(20));

create or replace function utilizador_regular_insert(emaill varchar(80), password varchar(20))
	returns void as

$$
	begin
	        if emaill not in (select email from utilizador_qualificado) then
                alter table utilizador disable trigger utilizador_bit;
			    insert into utilizador values(emaill, password);
			    insert into utilizador_regular values(emaill);
                alter table utilizador enable trigger utilizador_bit;
			else
	            raise exception 'Este utilizador ja e qualificado';
	        end if;
	end;
$$ language plpgsql;




