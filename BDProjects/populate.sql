----------------------------------------
-- Populate Relations
----------------------------------------

--Populate local_publico
insert into local_publico values('38.866606','-9.316332','Cafe O 17');
insert into local_publico values('38.826099','-9.171300','Farmacia Nova de Loures');
insert into local_publico values('39.091411','-9.211759','Cafe O Gancho');
insert into local_publico values('39.370082','-9.396691','Miradouro de Remedios');
insert into local_publico values('37.008633','-8.943147','Casa da pesca Falesia');
insert into local_publico values('37.021263','-7.937960','IMT Faro');
insert into local_publico values('40.655722','-7.917497','COULT STUDIO-Tatoo Art');
insert into local_publico values('38.554752','-7.905101','Decathlon Evora');
insert into local_publico values('37.722097','-8.787949','Praia da Franquia');
insert into local_publico values('39.336775','-8.936379','CineTeatro de Rio Maior');
insert into local_publico values('38.737565','-9.161342','Bankinter Columbano');
insert into local_publico values('38.775501','-9.095705','Tappas Caffe');

--Populate item
insert into item values(1,'Ementa','MonteLavar','38.866606','-9.316332');
insert into item values(2,'Horario','Loures','38.826099','-9.171300');
insert into item values(3,'Letreiro','MonteLavar','38.866606','-9.316332');
insert into item values(4,'Horario','Sagres','37.008633','-8.943147');
insert into item values(5,'Bilhete de Entrada','Rio Maior','39.336775','-8.936379');
insert into item values(6,'Tabela de Informacoes','Peniche','39.370082','-9.396691');
insert into item values(7,'Horario','Viseu','40.655722','-7.917497');
insert into item values(8,'Ementa','Matacaes','39.091411','-9.211759');
insert into item values(9,'Horario','Faro','37.021263','-7.937960');
insert into item values(10,'Catalogo','Evora','38.554752','-7.905101');
insert into item values(11,'Mapa da praia','Vila Nova de Mil Fontes','37.722097','-8.787949');
insert into item values(12,'Ementa','MonteLavar','38.866606','-9.316332');
insert into item values(13,'Ementa','Parque das Nacoes','38.775501','-9.095705');

--Populate anomalia

insert into anomalia values(1,'019,163,025,172','asd2323d.jpeg','Portugues','2016-06-22 19:10:25','Palavra caracois mal escrita.','true');
insert into anomalia values(2,'050,100,075,179','wekurhl.jpeg','Portugues','2020-03-28 10:47:25','Escreveram aberto das 10:00H as 25:00H.','true');
insert into anomalia values(3,'057,180,070,188','asdwknhlk.jpeg','Portugues','2020-05-17 14:10:00','Ao limparem o nome do restaurante trocaram duas letras.','true');
insert into anomalia values(4,'220,084,235,094','sadsbabdc.jpeg','Portugues','2020-12-22 15:30:43','Loja diz que fecha as 13:30 para almoco e reabre as 13:20.','true');
insert into anomalia values(5,'050,100,075,179','we98rtuw9.jpeg','Portugues','2020-05-10 12:53:35','Escreveram aberto das 10:00H as 25:00H.','true');
insert into anomalia values(6,'052,107,071,143','23e8923ehp.jpeg','Portugues','2020-01-14 16:20:40','Escreveram aberto das 10:00H as 25:00H.','true');
insert into anomalia values(7,'220,600,235,654','qo2ieoq32je.jpeg','Portugues','2020-09-14 19:10:25','Loja tem os horarios todos trocados.','true');
insert into anomalia values(8,'019,163,025,172','aeskrlahral.jpeg','Portugues','2020-06-22 21:10:25','Palavra caracois foi mal escrita.','true');
insert into anomalia values(9,'210,110,220,130','aaasjekxgsbc.jpeg','Portugues','2015-03-22 12:27:34','Miradouro mal traduzida para ingles.','false');
insert into anomalia values(10,'340,260,370,262','tatoo.jpeg','Portugues','2013-05-19 15:30:24','Palavra horario mal escrita.','true');
insert into anomalia values(11,'270,090,320,234','asd2323d.jpeg','Ingles','2014-01-27 10:10:30','Palavra horario mal escrita.','true');
insert into anomalia values(12,'030,100,067,120','aahhjkashhhshhs.jpeg','Ingles','2019-05-23 17:13:29','Palavra Miradouro mal traduzida para alemao.','false');
insert into anomalia values(13,'232,060,250,068','sadasdsdsg.jpeg','Portugues','2020-05-22 23:02:24','Palavra bilhete mal traduzida para ingles.','false');
insert into anomalia values(14,'080,122,172,140','rtyu.jpeg','Portugues','2020-05-13 18:56:40','Palavra bilhete mal traduzida para frances.','false');
insert into anomalia values(15,'080,100,172,122','asdasaedwojpwwedwe.jpeg','Portugues','2020-08-20 18:56:40','Ementa desformatada.','true');
insert into anomalia values(16,'050,023,080,037','dkasldhjaslkd.jpeg','Portugues','2020-08-20 18:56:40','Palavra Quarta-Feira mal escrita','true');
insert into anomalia values(17,'100,420,220,483','laskdufhikwel.jpeg','Portugues','2020-09-11 17:43:13','Palavra Futebol mal escrita','true');
insert into anomalia values(18,'120,430,140,475','ashubasasbasbxsbxs.jpeg','Portugues','2020-07-17 17:17:17','Palavra praia mal traduzida para frances','false');
insert into anomalia values(19,'120,230,130,240','saasdcbmsmh.jpeg','Portugues','2019-07-08 10:43:58','Palavra capuccino mal escrita','true');

--Populate anomalia_traducao
insert into anomalia_traducao values(9,'250,140,260,160','Ingles');
insert into anomalia_traducao values(12,'077,140,097,160','Alemao');
insert into anomalia_traducao values(13,'260,140,278,148','Ingles');
insert into anomalia_traducao values(14,'180,146,268,160','Frances');
insert into anomalia_traducao values(18,'150,480,180,525','Frances');


--Populate duplicado
insert into duplicado values(1,12);

--Populate utilizador


select utilizador_regular_insert('clucas@worksoho.tk','AwTUB85H');
select utilizador_regular_insert('lsambaeu.tuamule@tiodarrigh.tk','ez2aLNce');
select utilizador_regular_insert('fyvesnarson@nomusnik.tk','RptfE3TV');
select utilizador_regular_insert('kawtar@jazzzespo.gq','LU8mNQHP');


select utilizador_qualificado_insert('ijack.m@zvwjfk.us','EMDyNDpb');
select utilizador_qualificado_insert('malyani17k@leyfamug.gq','2jbmJTEj');
select utilizador_qualificado_insert('qhussameld@saupecmay.gq','fWSAqnaH');
select utilizador_qualificado_insert('aliikeesz@blaciser.tk','BxMd68wv');
select utilizador_qualificado_insert('maahi@tyuobq.space','LbdrKYYW');


--Populate incidencia

insert into incidencia values(1,1,'clucas@worksoho.tk');
insert into incidencia values(8,1,'aliikeesz@blaciser.tk');
insert into incidencia values(10,7,'maahi@tyuobq.space');
insert into incidencia values(4,4,'ijack.m@zvwjfk.us');
insert into incidencia values(7,4,'aliikeesz@blaciser.tk');
insert into incidencia values(11,7,'clucas@worksoho.tk');
insert into incidencia values(5,2,'qhussameld@saupecmay.gq');
insert into incidencia values(2,2,'qhussameld@saupecmay.gq');
insert into incidencia values(3,3,'aliikeesz@blaciser.tk');
insert into incidencia values(6,2,'aliikeesz@blaciser.tk');
insert into incidencia values(12,6,'kawtar@jazzzespo.gq');
insert into incidencia values(9,6,'malyani17k@leyfamug.gq');
insert into incidencia values(14,5,'lsambaeu.tuamule@tiodarrigh.tk');
insert into incidencia values(13,5,'kawtar@jazzzespo.gq');
insert into incidencia values(15,8,'aliikeesz@blaciser.tk');
insert into incidencia values(16,9,'aliikeesz@blaciser.tk');
insert into incidencia values(17,10,'aliikeesz@blaciser.tk');
insert into incidencia values(18,11,'aliikeesz@blaciser.tk');
insert into incidencia values(19,13,'maahi@tyuobq.space');

--Populate proposta_de_correcao

insert into proposta_de_correcao values('aliikeesz@blaciser.tk',1,'2020-05-06 15:38:28','Caracois em vez de caracoles');
insert into proposta_de_correcao values('aliikeesz@blaciser.tk',2,'2020-06-28 23:45:46','Escrever 24:00H ou 00:00H');
insert into proposta_de_correcao values('aliikeesz@blaciser.tk',3,'2020-03-12 10:15:26','Trocar o EF para FE');
insert into proposta_de_correcao values('aliikeesz@blaciser.tk',4,'2020-05-09 16:17:38','O dono deveria rever os horarios');
insert into proposta_de_correcao values('aliikeesz@blaciser.tk',5,'2020-01-19 14:05:21','A ementa deveria ser reformatada');
insert into proposta_de_correcao values('aliikeesz@blaciser.tk',6,'2020-12-06 11:03:59','Quarta-Feira em vez de Qoarta-Feira');
insert into proposta_de_correcao values('aliikeesz@blaciser.tk',7,'2020-10-04 10:37:20','Futebol em vez de Fotebol');
insert into proposta_de_correcao values('aliikeesz@blaciser.tk',8,'2020-07-23 12:34:30','Plage em vez de palage');
insert into proposta_de_correcao values('qhussameld@saupecmay.gq',9,'2020-05-10 20:45:46','Escrever 24:00H no horario do restaurante');
insert into proposta_de_correcao values('maahi@tyuobq.space',10,'2020-05-10 13:50:23','Escrever capuccino em vez de capuxino');
insert into proposta_de_correcao values('aliikeesz@blaciser.tk',11,'2020-01-19 15:45:40','Palavra capuccino mal escrita');

--Populate correcao

insert into correcao values('aliikeesz@blaciser.tk',1,8);
insert into correcao values('aliikeesz@blaciser.tk',2,6);
insert into correcao values('aliikeesz@blaciser.tk',3,3);
insert into correcao values('aliikeesz@blaciser.tk',4,7);
insert into correcao values('aliikeesz@blaciser.tk',5,15);
insert into correcao values('aliikeesz@blaciser.tk',6,16);
insert into correcao values('aliikeesz@blaciser.tk',7,17);
insert into correcao values('aliikeesz@blaciser.tk',8,18);
insert into correcao values('qhussameld@saupecmay.gq',9,5);
insert into correcao values('maahi@tyuobq.space',10,19);
insert into correcao values('aliikeesz@blaciser.tk',11,19);


