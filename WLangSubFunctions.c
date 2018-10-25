#include "WLang.h"


Tag *return_calculated_tag(Type calc_type, Tag *left ,Tag *right){
	Tag *result = malloc(sizeof(Tag));
	result->type = left->type;
	if(left->type == INT_TYPE && right->type == INT_TYPE){
		if(calc_type == ADD_TYPE){
			result->val.i = left->val.i + right->val.i;
		}else if(calc_type == SUB_TYPE){
			result->val.i = left->val.i - right->val.i;
		}else if(calc_type == MUL_TYPE){
			result->val.i = left->val.i * right->val.i;
		}else if(calc_type == DIV_TYPE){
			result->val.i = left->val.i / right->val.i;
		}else if(calc_type == MOD_TYPE){
			result->val.i = left->val.i % right->val.i;
		}
	}else if(left->type == DOUBLE_TYPE && right->type == DOUBLE_TYPE){
		if(calc_type == ADD_TYPE){
			result->val.d = left->val.d + right->val.d;
		}else if(calc_type == SUB_TYPE){
			result->val.d = left->val.d - right->val.d;
		}else if(calc_type == MUL_TYPE){
			result->val.d = left->val.d * right->val.d;
		}else if(calc_type == DIV_TYPE){
			result->val.d = left->val.d / right->val.d;
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