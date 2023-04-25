drop table if exists d_utilizador cascade;
drop table if exists d_tempo cascade;
drop table if exists d_local cascade;
drop table if exists d_lingua cascade;
drop table if exists f_anomalia cascade;


create table d_utilizador
    (id_utilizador numeric(10) not null unique,
    email          varchar(40) not null,
    tipo           varchar(15) not null,
    constraint pk_id_utilizador primary key (id_utilizador),
    constraint chk_tipo check(tipo in ('qualificado', 'regular')));

create table d_tempo
    (id_tempo      numeric(10) not null unique,
    dia            numeric(2) not null,
    dia_da_semana  varchar(20) not null,
    semana         numeric(2) not null,
    mes            varchar(10) not null,
    trimestre      integer not null,
    ano            numeric(4) not null,
    constraint pk_id_tempo primary key (id_tempo),
    constraint chk_dia check(dia between 1 and 31),
    constraint chk_semana check(semana between 1 and 52),
    constraint chk_trimestre check(trimestre between 1 and 4));

create table d_local
    (id_local      numeric(10) not null unique,
    latitude       varchar(15) not null,
    longitude      varchar(15) not null,
    nome           varchar(60) not null,
    constraint pk_id_local primary key (id_local));

create table d_lingua
    (id_lingua     numeric(10) not null unique,
    lingua         varchar(20) not null,
    constraint pk_id_lingua primary key (id_lingua));

create table f_anomalia
    (id_utilizador numeric(10) not null,
    id_tempo       numeric(10) not null,
    id_local       numeric(10) not null,
    id_lingua      numeric(10) not null,
    tipo_anomalia  varchar(15) not null,
    com_proposta   boolean not null,
    constraint pk_f_anomalia primary key (id_utilizador, id_tempo, id_local, id_lingua),
    constraint fk_id_utilizador foreign key (id_utilizador) references d_utilizador(id_utilizador),
    constraint fk_id_tempo foreign key (id_tempo) references d_tempo(id_tempo),
    constraint fk_id_local foreign key (id_local) references d_local(id_local),
    constraint fk_id_lingua foreign key (id_lingua) references d_lingua(id_lingua),
    constraint chk_tipo_anomalia check(tipo_anomalia in ('redacao', 'traducao')));
