/* Exercicio de indices 4.1
Como a base de dados pode se apresentar com uma
estrutura heap, não é adequado usar um hash index porque não vai otimizar
a WHERE clause.Portanto , vamos criar um índice sobre o GROUP BY.
Como, por natureza, o GROUP BY tem um algoritmo de SORT,
ao criarmos um non-clustered index,saltar-se-á o SORT
do GROUP BY e será feito um INDEX ONLY SCAN para resolver a query.
 */
DROP INDEX incidencia_item_id_idx;

CREATE INDEX incidencia_item_id_idx
ON incidencia (item_id);




/* Exercicio de indices 4.2
Escolhemos utilizar b+ tree composite <lingua,ts> dado que a query pede valores de ts entre dois valores,
algo que o hash index não suporta.
A escolha entre a ordem da composite key deve-se ao facto de ser mais rápido indexar primeiro
por lingua(onde neste projeto irá haver menos variações e portanto mais resultados) e posteriormente
indexar por ts que , de acordo com o contexto do projeto, tem muito mais espaço para valores diferentes
e será espetável obter menos resultados quando indexamos de acordo com um certo intervalo de valores.
Dado que a variável tem_anomalia_redaçao é um booleano, a quantidade de registos de anomalia de redação apurados seria
aproximadamente metade de todas as anomalias registadas, o que levaria a uma indexagem muito pobre, desnecessária e
lenta.Logo apenas cria-se sobre o indice sobre os registos que validam a condição tem_anomalia_redacao = 'true'
 */
DROP INDEX anomalia_lingua_ts_idx;

CREATE INDEX anomalia_lingua_ts_idx
ON anomalia(lingua,ts) WHERE tem_anomalia_redacao = 'true';


