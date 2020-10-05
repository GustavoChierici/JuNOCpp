# JuNOC++/JuNOCpp 0.2.3
### Just a Notification Oriented C++
###### Rule* rlHelloWorld = new Rule();

JuNOC++ é um mini framework (porcamente programado até agora) de C++ que materializa (ainda de forma bem prototipal) o Paradigma Orientado a Notificações (PON). Mas o que é o PON? Como o próprio nome diz, o Paradigma Orientado a Notificações é um novo paradigma de programação (e também de computação em si), proposto inicialmente pelo professor Dr. Jean Marcelo Simão, docente atual da Universidade Tecnológica Federal do Paraná, Câmpus Curitiba, na qual ele leciona matérias de programação para graduação e pós-graduação. O propósito do PON é resolver as deficiências estruturais e temporais dos demais paradigmas, que podem ser separados basicamente entre Paradigma Imperativo (POO e Progamação Procedural) e Paradigma Declarativo (Programação Lógica e Programação Funcional), por meio de entidades notificantes "inteligentes", responsáveis por reprensentar o conhecimento lógico-causal e realizar os cálculos lógicos causais, sem dependerem de estruras de controle redundantes, estrututuras de dados custosas e buscas. 
O PON é composto por basicamente 8 entidades básicas, são elas:  
* FBEs (FactBaseElements)   
* Attributes  
* Premises  
* Conditions    
* Rules  
* Actions  
* Instigations  
* Methods

Sendo que apenas as 5 primeiras são estritamente necessárias, dependendo do ambiente em que se está trabalhando.  
  
### FBEs  
FBEs são entidades semelhantes as classes do POO, elas possuem referências para Attributes e Methods e representam os elementos normais do dia a dia (como um arqueiro e uma maçã).  
Para criar um FBE, derive a classe FBE do framework e inclua o header da classe do tipo de Attribute que será utilizado.  
  
### Attributes  
Attributes são entidades notificantes que encapsulam os atributos de um FBE e os tipos de dados principais (int, float, boolean, string, ...). Quando o estado de um Attribute é alterado, ele notifica pontualmente as Premises que estejam interessadas nessa mudança de seu estado, por meio de uma tabela hash para que esse processo seja ainda mais eficiente. Attributes devem ser criados (preferencialmente) dentro de FBEs de forma dinâmica.  
  
### Premises  
Premises são as entidades que cuidam da avaliação lógica entre um Attribute e um determinado valor desejado. Assim como os Attributes, as Premises também guardam seus estados lógicos e, assim que alterado, elas notificam pontualmente as Conditions que dependam delas. Premises ainda podem ser do tipo EQUAL (==), NOT_EQUAL (!=), GREATER_THAN (>), GREATHER_OR_EQUAL_THAN (>=), LESS_THAN (<) e LESS_OR_EQUAL_THAN (<=). Premises podem ser criadas dentro Rules, Conditions, SubConditions ou separadamente, caso você queira compartilhá-la para mais de uma Rule. Uma Premise pode ser criada separadamente da seguinte maneira:  
  
_Premise* nome_da_premise = new Premise(&attribute_referenciado_pela_premise, valor_desejado_para_que_premise_seja_aprovada, tipo_da_premise /\*(string) - "EQUAL"(default)\*/);_  
  
### Conditions
Conditions são, """basicamente""" (sim, entre muitas aspas mesmo), contadores de Premises aprovadas. Elas representam a condição para que uma determinada Rule seja aprovada, estando ligadas a uma e somente uma Rule. Quando todas as Premises necessárias para a aprovação de Condition são aprovadas, a Condition notifica a Action da Rule a qual ela pertence. Uma Condition pode ser do tipo CONJUNCTION (e/and/&&) ou DISJUNCTION (ou/or/||), sendo que basta passar esse parâmetro para o construtor dela ou da Rule para definir seu tipo.  
#### SubConditions  
SubConditions são uma espécie de fusão de Conditions com Premises. Elas também são do tipo CONJUNCTION ou DISJUNCTION e também são "contadores de Premises aprovadas", mas quando uma SubCondition é aprovada, em vez dela notificar uma Rule, ela notifica um Condition ou uma outra SubCondition "mãe" na qual ela está ligada. Com SubConditions, podemos criar expressões lógicas bem mais complexas do que com apenas Conditions.  
  
### Rules  
Rules são as regras que regem o funcionamento do código. Uma Rule é composta por uma Condition e por uma Action, sendo a quinta e última entidade estritamente necessária ao PON. Em ambientes onde não existem as demais 4 entidades, elas são substituídas pelo método execute dentro de uma Rule. Quando você quer utilizar todas as entidades do PON, as Rules serão do tipo COMPLETE, já quando você quiser apenas usar as 5 primeiras entidades do PON, elas serão do tipo INCOMPLETE. Uma Rule pode ser criada da seguinte forma:  
  
_Rule* nome_da_rule = new Rule(tipo_da_condition_da_rule/\*(string) - "CONJUNCTION"(default) ou "DISJUNCTION"\*/, tipo_da_Rule /\*(int) Rule::COMPLETE (0) (default)\*/);   
nome_da_rule->addPremise(&attribute_a_ser_referenciado_na_premise, valor_desejado_para_que_premise_seja_aprovada, tipo_da_premise);  
nome_da_rule->addPremise(&premise_criada_separadamente);  
nome_da_rule->addSubCondition(tipo_da_subcondition); //SubCondition 1  
nome_da_rule->addPremiseToSubCondition(...);  //SubCondition 1   
nome_da_rule->addPremiseToSubCondition(...); //SubCondition 1  
nome_da_rule->addSubCondition(...); //SubCondition 2  
nome_da_rule->addPremiseToSubCondition(...); //SubCondition 2  
..._
  
Quando usar Complete Rules, as seguintes linhas devem ser usadas:  
  
_nome_da_rule->addInstigation(&instigation_criada_separadamente);
nome_da_rule->addInstigation(&method_criado_separadamente);
nome_da_rule->addInstigation(&attribute_a_ser_modificado_pela_rule_quando_aprovadao, valor_que_será_atribuído_ao_attribute);_
  
Quando usar Incomplete Rules, use isto no lugar:
  
_nome_da_rule->referenceAttr(&attribute_a_ser_modificado_pela_rule_quando_aprovada, valor_que_será_atribuído_ao_attribute);_  
  
###### Obs: A nomenclatura de Incomplete e Complete Rules foi dada por mim mesmo, ela não faz parte da literatura atual do PON.
###### Obs2: Por hora, apenas um Attribute pode ser modificado numa Incomplete Rule.
  
### Actions  
Actions são entidades que guardam referências para Instigations. Elas são responsáveis por iniciar o fluxo de notificações que irá modificar os estados dos Attributes posteriormente. Pode-se entender como o equivalente das Conditions no fluxo facto-exucional/secundário de notificações.  
  
### Instigations  
Instigations são entidades que encapsulam as entidades Methods, sendo comparáveis as Premises com os Attributes, visto que, tal qual uma Premise pode ser compartilhada com várias Conditions, uma Instigation pode ser compartilhada com várias Actions. Assim que uma Instigation é chamada, ela chama o Method que está associado a mesma.  
  
### Methods  
Methods, por fim, são entidades que encapsulam os métodos de um FBE, responsáveis por alterarem os estados de seus determinados Attributes, reiniciando assim, o ciclo de notificações.  

###### Uma explicação muito mais detalhada sobre o PON, suas qualidades e sobre paradigmas de computação pode ser encontrada na dissertação de mestrado de Roni Fabio Banaszewski (http://livros01.livrosgratis.com.br/cp087456.pdf).

Para facilitar o entendimento do funcionamento do JuNOC++, junto dos arquivos do framework, está também um exemplo, comparando o JuNOC++ com o POO, num experimento bem semelhante ao feito por Banaszewski na subseção 5.2.4.1 de sua dissertação de mestrado.

Por fim, esse é um projeto que, por hora, pretendo seguir sozinho. O PON foi uma coisa que me encantou quando eu comecei a estudá-lo no meio dessa pandemia de Covid-19, então sei lá, sinto que, de alguma forma, ajudar a transformar o PON num paradigma mais maduro é a minha primeira contribuição real para a humanidade, mesmo que o PON, apesar de todo o meu esforço, não se torne realmente relevante. Conto com o feedback das talvez 5 pessoas (ou menos) que irão dar uma olhada no JuNOC++ para torná-lo numa materialização melhor desse paradigma tão promissor.
