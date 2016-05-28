// Note: newline only appears as a token when lexing %token
%token IDENTIFIER TERMINAL COLON BAR SEMICOLON TOKEN NEWLINE SEMICOLON EMPTY


%start start

%%

start : define_terminals statements | statements ;

statements : statements production_rule | production_rule ;

define_terminals : TOKEN terminal_list NEWLINE ;

terminal_list : terminal_list IDENTIFIER | IDENTIFIER ;

production_rule :
	IDENTIFER COLON symbol_list BAR production_rule |
	IDENTIFER COLON symbol_list COLON
	;

symbol_list : symbol_list symbol | symbol | EMPTY ;

symbol : IDENTIFER | TERMINAL ;

%%
