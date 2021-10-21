# Plan

La idea principal, es ordenar todos los registros concurrencia, después de eso, haremos un priority queue cuya prioridad se definirá por el día de cada registro.  

### Necesitamos: 

1. Hashmap 
2. Distinguir número de concurrencias 

## Paso 1: Ordenar por número de acceso (concurrencia)

## Paso 2: Pasar el vector ordenado a un priority queue

## Paso 3: Hacer un dequeue con prioridad en base al día, guardar ese resultado en un vector,

# Estructura del código
## Clase error
En la clase error, tendremos un atributo correspondiente a su IP, un atributo correspodiente a su prioridad en base a fecha.
## Hashmap
Agarra como key el día y la IP, para contar las concurencia por día.