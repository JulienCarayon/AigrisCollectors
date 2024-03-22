# MISRA-C

Vérification la conformité des programmes écrits en C avec certaines des règles de la norme de développement logiciel [MISRA-C:2004](http://en.wikipedia.org/wiki/MISRA_C).

Les vérifications des règles suivantes sont mises en œuvre :

### √ Règle 2.2 (requise) : Le code source ne doit utiliser que des commentaires de style `/*` ... `*/`.

### √ Règle 2.3 (requise) : La séquence de caractères /* ne doit pas être utilisée dans un commentaire.

### √ Règle 4.1 (requise) : Seules les séquences d'échappement définies dans la norme ISO C doivent être utilisées.

Autorisées : 

        \'  \"  \?  \\  \a  \b  \f  \n  \r  \t  \v  \0

Non autorisées :

        \0... chiffre-octal
        \x... chiffre-hexadécimal

### √ Règle 4.2 (requise) : Les trigraphes ne doivent pas être utilisés.

        ??=  ??(  ??/  ??)  ??'  ??<  ??!  ??>  ??- 

### √ Règle 5.1 (requise) : Les identificateurs (internes et externes) ne doivent pas reposer sur la signification de plus de 31 caractères.

### √ Règle 7.1 (requise) : Les constantes octales (autres que zéro) et les séquences d'échappement octales ne doivent pas être utilisées.

### √ Règle 14.4 (requise) : L'instruction goto ne doit pas être utilisée.

### √ Règle 14.5 (requise) : L'instruction continue ne doit pas être utilisée.

### √ Règle 19.6 (requise) : #undef ne doit pas être utilisé.

### √ Règle 19.13 (conseillée) : Les opérateurs # et ## ne devraient pas être utilisés.

Les vérifications des règles suivantes sont prévues d'être mises en œuvre :

### Règle 12.10 (requise) : L'opérateur virgule ne doit pas être utilisé.

### Règle 12.13 (conseillée) : Les opérateurs d'incrémentation (++) et de décrémentation (--) ne devraient pas être mélangés avec d'autres opérateurs dans une expression.

### Règle 13.1 (requise) : Les opérateurs d'assignation ne doivent pas être utilisés dans des expressions qui produisent une valeur booléenne.

### Règle 14.3 (requise) : Avant la préparation, une instruction nulle ne doit apparaître que sur une ligne à part entière ; elle peut être suivie d'un commentaire à condition que le premier caractère suivant l'instruction nulle soit un caractère d'espace blanc.

### Règle 14.6 (requise) : Pour toute instruction d'itération, il ne doit y avoir au plus qu'une seule instruction break utilisée pour la terminaison de la boucle.

### Règle 14.7 (requise) : Une fonction doit avoir un seul point de sortie à la fin de la fonction.

### Règle 14.8 (requise) : L'instruction formant le corps d'une instruction switch, while, do ... while ou for doit être une instruction composée.

### Règle 14.9 (requise) : Une construction if (expression) doit être suivie d'une instruction composée. Le mot-clé else doit être suivi soit d'une instruction composée, soit d'une autre instruction if.

### Règle 14.10 (requise) : Toutes les constructions if ... else if doivent se terminer par une clause else.

### Règle 15.3 (requise) : La clause finale d'une instruction switch doit être la clause par défaut.

### Règle 15.5 (requise) : Chaque instruction switch doit avoir au moins une clause case.

### Règle 19.1 (conseillée) : Les instructions #include dans un fichier ne devraient être précédées que d'autres directives de préprocesseur ou de commentaires.

### Règle 19.2 (conseillée) : Les caractères non standard ne devraient pas apparaître dans les noms de fichiers d'en-tête dans les directives #include.

### Règle 19.5 (requise) : Les macros ne doivent pas être #define'd ou #undef'd à l'intérieur d'un bloc.

### Règle 19.12 (requise) : Il ne doit y avoir au plus qu'une occurrence des opérateurs # ou ## dans une seule définition de macro.