drop table if exists local_publico cascade;
drop table if exists item cascade;
drop table if exists anomalia cascade;
drop table if exists anomalia_traducao cascade;
drop table if exists duplicado cascade;
drop table if exists utilizador cascade;
drop table if exists utilizador_qualificado cascade;
drop table if exists utilizador_regular cascade;
drop table if exists incidencia cascade;
drop table if exists proposta_de_correcao cascade;
drop table if exists correcao cascade;

----------------------------------------
-- Table Creation
----------------------------------------

-- Named constraints are global to the database.
-- Therefore the following use the following naming rules:
--   1. pk_table for names of primary key constraints
--   2. fk_table_another for names of foreign key constraints

create table local_publico
    (latitude   decimal(9,6) not null,
     longitude  decimal(9,6) not null,
     nome       varchar(80) not null,
     constraint pk_local_publico primary key(latitude,longitude),
     constraint chk_lat check(latitude between -90 and 90),
     constraint chk_lon check(longitude between -180 and 180));

create table item
    (id             numeric(10) not null,
     descricao      text not null,
     localizacao    varchar(80) not null,
     latitude       decimal(9,6) not null,
     longitude      decimal(9,6) not null,
     constraint pk_item primary key(id),--------------
     constraint fk_item_local_publico foreign key(latitude,longitude) references local_publico(latitude,longitude)on delete cascade on update cascade,
     constraint chk_lat check(latitude between -90 and 90),
     constraint chk_lon check(longitude between -180 and 180));

create table anomalia
    (id             numeric(10) not null,
     zona           varchar(16) not null,
     imagem         varchar(60) not null,
     lingua         varchar(20) not null,
     ts             timestamp not null,
     descricao      text not null,
     tem_anomalia_redacao   boolean not null,
     constraint pk_anomalia primary key(id),
     constraint chk_imagem check(imagem like '%.jpeg'),
     constraint chk_redacao check(tem_anomalia_redacao in('true','false')));


create table anomalia_traducao
    (id     numeric(10) not null,
    zona2   varchar(16) not null,--(___,___,___,___\n)
    lingua2 varchar(20) not null,
    constraint pk_anomalia_traducao primary key(id),
    constraint fk_anomalia_traducao_anomalia foreign key(id) references anomalia(id) on delete cascade on update cascade);

create table duplicado
    (item1  numeric(10) not null,
    item2   numeric(10) not null,
    constraint pk_duplicado primary key (item1,item2),
    constraint fk_duplicado_item1 foreign key (item1) references item(id)on delete cascade on update cascade,
    constraint fk_duplicado_item2 foreign key (item2) references item(id)on delete cascade on update cascade);

create table utilizador
    (email      varchar(80) not null,
    password    varchar(20) not null,
    constraint pk_utilizador primary key (email),
    constraint chk_email check(email like '%@%'));

create table utilizador_qualificado
    (email  varchar(80) not null,
    constraint pk_utilizador_qualificado primary key (email),
    constraint fk_utilizador_qualificado_utilizador foreign key (email) references utilizador(email)on delete cascade on update cascade,
    constraint chk_email check(email like '%@%'));

create table utilizador_regular
    (email  varchar(80) not null,
    constraint pk_utilizador_regular primary key (email),
    constraint fk_utilizador_regular_utilizador foreign key (email) references utilizador(email)on delete cascade on update cascade,
    constraint chk_email check(email like '%@%'));

create table incidencia
    (anomalia_id    numeric(10) not null,
    item_id         numeric(10) not null,
    email           varchar(80) not null,
    constraint pk_incidencia primary key (anomalia_id),
    constraint fk_incidencia_anomalia foreign key (anomalia_id) references anomalia(id)on delete cascade on update cascade,
    constraint fk_incidencia_item foreign key (item_id) references item(id)on delete cascade on update cascade,
    constraint fk_incidencia_utilizador foreign key (email) references utilizador(email));

create table proposta_de_correcao
    (email      varchar(80) not null,
    nro         numeric(10) not null ,
    data_hora   timestamp not null,
    texto       text not null,
    constraint pk_proposta_de_correcao primary key (email,nro),
    constraint fk_proposta_de_correcao_utilizador_qualificado foreign key (email) references utilizador_qualificado(email),
    constraint chk_email check(email like '%@%'));

create table correcao
    (email      varchar(80) not null,
    nro         numeric(10) not null,
    anomalia_id numeric(10) not null,
    constraint pk_correcao primary key (email,nro,anomalia_id),
    constraint fk_correcao_proposta_de_correcao foreign key (email,nro) references proposta_de_correcao(email,nro)on delete cascade on update cascade,
    constraint fk_correcao_incidencia foreign key (anomalia_id) references incidencia(anomalia_id)on delete cascade on update cascade,
    constraint chk_email check(email like '%@%'));

