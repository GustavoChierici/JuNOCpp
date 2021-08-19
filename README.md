# JuNOC++/JuNOCpp - But Better 
### Just a Notification Oriented C++ (But Better)  
###### RULE(helloWorld->helloTime == true);   
###### &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;INSTIGATE(\[=](){helloWorld->sayHello();});  
###### END_RULE  
   
JuNOC++ é um mini framework (porcamente programado até agora) de C++ que materializa (ainda de forma bem prototipal) o Paradigma Orientado a Notificações (PON). Esta versão do framework é um versão que testa a viabilidade de uma nova forma inovadora de se compor as Rules do PON, sendo muito mais simples e intuitiva de ser utilizada. E sim, o "But Better" é uma referência ao quadro do Joshua Weissman em seu canal do Youtube, e eu chamei essa versão assim por conta de as classes dessa versão alternativa possuirem a palavra Better na frente.

Mas o que é o PON? Como o próprio nome diz, o Paradigma Orientado a Notificações é um novo paradigma de programação (e também de computação em si), proposto inicialmente pelo professor Dr. Jean Marcelo Simão, docente atual da Universidade Tecnológica Federal do Paraná, Câmpus Curitiba, na qual ele leciona matérias de programação para graduação e pós-graduação. O propósito do PON é resolver as deficiências estruturais e temporais dos demais paradigmas, que podem ser separados basicamente entre Paradigma Imperativo (POO e Progamação Procedural) e Paradigma Declarativo (Programação Lógica e Programação Funcional), por meio de entidades notificantes "inteligentes", responsáveis por reprensentar o conhecimento lógico-causal e realizar os cálculos lógicos causais, sem dependerem de estruras de controle redundantes, estrututuras de dados custosas e buscas. 
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
  
### Attributes  
Attributes são entidades notificantes que encapsulam os atributos de um FBE. Quando o estado de um Attribute é alterado, ele notifica pontualmente as Premises que estejam interessadas nessa mudança de seu estado, por meio de uma tabela hash para que esse processo seja ainda mais eficiente. Attributes devem ser criados (preferencialmente) dentro de FBEs. Um exemplo de attribute é o seguinte:  
  
_NOP::Attribute\<int> my_int_attr;_
  
### Premises  
Premises são as entidades que cuidam da avaliação lógica entre um Attribute e um determinado valor desejado. Assim como os Attributes, as Premises também guardam seus estados lógicos e, assim que alterado, elas notificam pontualmente as Conditions que dependam delas. Premises ainda podem ser do tipo EQUAL (==), NOT_EQUAL (!=), GREATER_THAN (>), GREATER_OR_EQUAL_THAN (>=), LESS_THAN (<) e LESS_OR_EQUAL_THAN (<=). Premises podem ser criadas dentro Rules, Conditions ou separadamente, caso você queira compartilhá-la para mais de uma Rule. Uma Premise pode ser criada separadamente da seguinte maneira:  
  
_NOP::Premise\<int> shared_premise = fbe1->my_int_attr1 == fbe2->my_int_attr2;_  

  
### Conditions
Conditions são, """basicamente""" (sim, entre muitas aspas mesmo), contadores de Premises aprovadas. Elas representam a condição para que uma determinada Rule seja aprovada. Quando todas as Premises necessárias para a aprovação de Condition são aprovadas, a Condition notifica a Rule a qual ela pertence. Conditions também podem conter outras Conditions dentro de si, para criar condições mais complexas, sendo que, nesse caso, a Condition filha notifica a Condition mãe, em vez de uma Rule, e Conditions podem ser compartilhadas. Um exemplo de criação de Condition para ser compartilhada se dá logo abaixo:  
  
_NOP::Condition shared_condition = SharedCondition(shared_premise and (fbe1->my_bool_attr == true or fbe2->my_bool_attr == false));_
  
### Rules  
Rules são as regras que regem o funcionamento do código. Uma Rule é composta por uma Condition e por uma Action, sendo a quinta e última entidade estritamente necessária ao PON. Em ambientes onde não existem as demais 4 entidades, elas são substituídas pelo método execute dentro de uma Rule. Uma Rule pode ser criada da seguinte forma:  
  
_RULE(shared_condition and fbe3->my_float_attr <= 32.7);  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;INSTIGATE(\[=](){fbe3->my_float_attr = 123.2;});  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;INSTIGATE(\[=](){fbe4->my_bool_attr = true;});  
END_RULE_
  
###### Obs: Por hora, o lambda passado dentro da macro INSTIGATE é de total responsabilidade do desenvolvedor, devendo ele lidar com as questões de escopo.

### Actions*  
Actions são entidades que guardam referências para Instigations. Elas são responsáveis por iniciar o fluxo de notificações que irá modificar os estados dos Attributes posteriormente. Pode-se entender como o equivalente das Conditions no fluxo facto-exucional/secundário de notificações.  
  
### Instigations*  
Instigations são entidades que encapsulam as entidades Methods e blocos de código de execução, sendo comparáveis as Premises com os Attributes, visto que, tal qual uma Premise pode ser compartilhada com várias Conditions, uma Instigation pode ser compartilhada com várias Actions. Assim que uma Instigation é chamada, ela chama os Method e/ou o bloco de código que está associado a mesma.  
  
### Methods*  
Methods, por fim, são entidades que encapsulam os métodos de um FBE, responsáveis por alterarem os estados de seus determinados Attributes e outras funções importantes, reiniciando assim, o ciclo de notificações.  

###### *Actions, Instigations e Methods ainda não podem ser criados separadamente nessa versão do JuNOC++ But Better. 

###### Uma explicação muito mais detalhada sobre o PON, suas qualidades e sobre paradigmas de computação pode ser encontrada na dissertação de mestrado de Roni Fabio Banaszewski (http://livros01.livrosgratis.com.br/cp087456.pdf).

Para facilitar o entendimento do funcionamento do JuNOC++, junto dos arquivos do framework, está também um exemplo, comparando o JuNOC++ com o POO, num experimento bem semelhante ao feito por Banaszewski na subseção 5.2.4.1 de sua dissertação de mestrado. Há também um experimento que simula o funcionamento de uma porta automática.

Por fim, esse é um projeto que, até então, fiz sozinho, mas daqui pra frente procurarei ajuda para torná-lo cada vez melhor e transformá-lo numa materialização séria, estável, relevante e, principalmente, de livre acesso do PON. O PON foi uma coisa que me encantou quando eu comecei a estudá-lo no meio dessa pandemia de COVID-19, então sei lá, sinto que, de alguma forma, ajudar a transformar o PON num paradigma mais maduro é a minha primeira contribuição real para a humanidade, mesmo que o PON, apesar de todo o meu esforço, não se torne realmente relevante. Conto com o feedback das talvez 5 pessoas (ou menos) que irão dar uma olhada no JuNOC++ para torná-lo numa materialização melhor desse paradigma tão promissor.
