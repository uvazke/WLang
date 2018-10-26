#include "WLang.h"
static int VARIABLE_BUFFER_SIZE = 100;

Tag *return_calculated_tag(Type calc_type, Tag *left ,Tag *right){
	Tag *result = malloc(sizeof(Tag));
	Tag *tmp_left = malloc(sizeof(Tag));
	Tag *tmp_right = malloc(sizeof(Tag));
	
	if(left->type == STR_TYPE){
		tmp_left = call_variable(left);
		if(tmp_left == NULL){
			return result;
		}
	}else{
		tmp_left = left;
	}
	if(right->type == STR_TYPE){
		tmp_right = call_variable(right);
		if(tmp_right == NULL){
			return result;
		}
	}else{
		tmp_right = right;
	}

	result->type = tmp_left->type;
	if(tmp_left->type == INT_TYPE && tmp_right->type == INT_TYPE){
		if(calc_type == ADD_TYPE){
			result->val.i = tmp_left->val.i + tmp_right->val.i;
		}else if(calc_type == SUB_TYPE){
			result->val.i = tmp_left->val.i - tmp_right->val.i;
		}else if(calc_type == MUL_TYPE){
			result->val.i = tmp_left->val.i * tmp_right->val.i;
		}else if(calc_type == DIV_TYPE){
			result->val.i = tmp_left->val.i / tmp_right->val.i;
		}else if(calc_type == MOD_TYPE){
			result->val.i = tmp_left->val.i % tmp_right->val.i;
		}
	}else if(tmp_left->type == DOUBLE_TYPE && tmp_right->type == DOUBLE_TYPE){
		if(calc_type == ADD_TYPE){
			result->val.d = tmp_left->val.d + tmp_right->val.d;
		}else if(calc_type == SUB_TYPE){
			result->val.d = tmp_left->val.d - tmp_right->val.d;
		}else if(calc_type == MUL_TYPE){
			result->val.d = tmp_left->val.d * tmp_right->val.d;
		}else if(calc_type == DIV_TYPE){
			result->val.d = tmp_left->val.d / tmp_right->val.d;
		}
		//mod is invalid operand for double variables.
	}
	return result; 
}

Tag *return_expr(Tag *tag){
	Tag *result = malloc(sizeof(Tag));
	if(tag->type == INT_TYPE){
		result->type = INT_TYPE;
		result->val.i = tag->val.i;
	}else if(tag->type == DOUBLE_TYPE){
		result->type = DOUBLE_TYPE;
		result->val.d = tag->val.d;
	}else if(tag->type == STR_TYPE){
		result->type = STR_TYPE;
		result->val.str = tag->val.str;
	}
	return result;
}

Tag *return_empty(){
	Tag *result = malloc(sizeof(Tag));
	result->type = EMPTY_TYPE;
	return result;
}
void print_val(Tag *tag){
	if(tag->type == INT_TYPE){
		printf("%d\n", tag->val.i);
	}else if(tag->type == DOUBLE_TYPE){
		printf("%lf\n", tag->val.d);
	}else if(tag->type == STR_TYPE){
		printf("%s\n", tag->val.str);
	}
}

void add_variable(Tag *left,Tag *right){
	if(left->type==STR_TYPE){
		char *buffer = TrimVARIABLE(left);
		if(buffer == NULL)return;
		int k=search_variable(buffer);
		if(k>=0){
			fprintf(stderr, "warning: variable %s is overwritten.\n", VARIABLE_BUFFER[k]);
			if(right->type == INT_TYPE){
				VARIABLE_VALUES_I[k] = right->val.i;
				VARIABLE_TYPE[k] = INT_TYPE;
			}else if(right->type == DOUBLE_TYPE){
				VARIABLE_VALUES_D[k] = right->val.d;
				VARIABLE_TYPE[k] = DOUBLE_TYPE;
			}else fprintf(stderr, "It's not a number.\n");
			return;
		}
		int len = strlen(buffer);
		if(VARIABLE_BUFFER_USED_LENGTH < VARIABLE_BUFFER_SIZE){
			strncpy(VARIABLE_BUFFER[VARIABLE_BUFFER_USED_LENGTH], buffer, len);
			if(right->type == INT_TYPE){
				VARIABLE_VALUES_I[VARIABLE_BUFFER_USED_LENGTH] = right->val.i;
				VARIABLE_TYPE[VARIABLE_BUFFER_USED_LENGTH] = INT_TYPE;
			}else if(right->type == DOUBLE_TYPE){
				VARIABLE_VALUES_D[VARIABLE_BUFFER_USED_LENGTH] = right->val.d;
				VARIABLE_TYPE[VARIABLE_BUFFER_USED_LENGTH] = DOUBLE_TYPE;
			}else fprintf(stderr, "It's not a number.\n");
			VARIABLE_BUFFER_USED_LENGTH += 1;
			fprintf(stderr, "memorize variables.\n");
		}
		else fprintf(stderr, "Sorry, there is no more room to memorize variables.\n");
	}
}

void print_variable(Tag *tag){
	if(tag->type==STR_TYPE){
		char *buffer = TrimSMCLNandOperators(tag);
		for(int i=0;i<VARIABLE_BUFFER_USED_LENGTH;i++){
			if(strcmp(VARIABLE_BUFFER[i],buffer)==0){
				if(VARIABLE_TYPE[i]==INT_TYPE)printf("%d\n",VARIABLE_VALUES_I[i]);
				if(VARIABLE_TYPE[i]==DOUBLE_TYPE)printf("%lf\n",VARIABLE_VALUES_D[i]);
			}
		}
	}
	//return 0;
}

int search_variable(char *str){
	if(VARIABLE_BUFFER_USED_LENGTH > 0 && VARIABLE_BUFFER_USED_LENGTH < VARIABLE_BUFFER_SIZE){
		for(int i=0;i<VARIABLE_BUFFER_USED_LENGTH;i++){
			if(strcmp(VARIABLE_BUFFER[i],str)==0)return i; 
		}
	}
	return -1;
}

Tag *call_variable(Tag *tag){
	Tag *result = malloc(sizeof(char*));
	if(tag->type==STR_TYPE){
		char *buffer = TrimSMCLNandOperators(tag);
		for(int i=0;i<VARIABLE_BUFFER_USED_LENGTH;i++){
			if(strcmp(VARIABLE_BUFFER[i],buffer)==0){
				if(VARIABLE_TYPE[i]==INT_TYPE){
					result->type = INT_TYPE;
					result->val.i = VARIABLE_VALUES_I[i];
					return result;
				}
				if(VARIABLE_TYPE[i]==DOUBLE_TYPE){
					result->type = DOUBLE_TYPE;
					result->val.d = VARIABLE_VALUES_D[i];
					return result;
				}
			}
		}
	} 
	return NULL;
}

char *TrimSMCLNandOperators(Tag* tag){
	if(tag->type == STR_TYPE){
		char *result = malloc(sizeof(char*));
		int num=0;  
		for(int i=0;i<strlen(tag->val.str);i++){
			if(tag->val.str[i] != ' ' && tag->val.str[i] != ';' && tag->val.str[i] != '='){
				if(tag->val.str[i] == '+' || tag->val.str[i] == '-' || tag->val.str[i] == '*' || tag->val.str[i] == '/' || tag->val.str[i] == '%' || tag->val.str[i] == ')')return result;
				result[num] = tag->val.str[i];
				num++;
			}
		}
		return result;
	}
	return NULL;
}

char *TrimVARIABLE(Tag* tag){
	int space_count=0;
	if(tag->type == STR_TYPE){
		char *result = malloc(sizeof(char*));
		int num=0;  
		for(int i=0;i<strlen(tag->val.str);i++){
			if(tag->val.str[i] == ';')return NULL;
			else{
				if(tag->val.str[i] == ' '){
					if(num>0)space_count++;
				}else if(tag->val.str[i] != '=' && space_count >0)return NULL;//remove variable like "ho ge" or "h o ge" 
				else{
					if(tag->val.str[i] == '=')return result;
					result[num] = tag->val.str[i];
					num++;
				}
			}
			
		}
		return result;
	}
	return NULL;
}



