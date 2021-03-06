#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "test_opt.h"

#define HELP_MAX 32 //maximum number of lines in help string

const int  opt_data_type_n_names  = 4;
const char *opt_data_type_names[] = {"double", "float", "double_complex", "float_complex"};
const char *opt_data_type_descs[] = {"double precision", "single precision", "complex double precision", "complex single precision"};

static void opt_fprintf_option(FILE *f, opt_option option) {
  char* token;
  char buffer[LINE_MAX * HELP_MAX];

  strncpy(buffer, option.header.help, LINE_MAX*HELP_MAX);

  token = strtok(buffer, "\n");
  if(token){
    fprintf(f, "-%c, --%-12s: %.60s\n", option.header.short_name, option.header.long_name, token);
    token = strtok(NULL, "\n");
    while(token){
      fprintf(f, "                    %.60s\n", token);
      token = strtok(NULL, "\n");
    }
  }else{
    fprintf(f, "-%c, --%-12s:\n", option.header.short_name, option.header.long_name);
  }
  token = strtok(NULL, "\n");
  fprintf(f, "                    (");
  switch(option.type){
    case opt_flag:
      fprintf(f, "flag)\n");
      break;
    case opt_int:
      if(option._int.required){
        fprintf(f, "required ");
      }
      fprintf(f, "int) values=[%d, %d] default=%d\n", option._int.min, option._int.max, option._int.value);
      break;
    case opt_string:
      if(option._string.required){
        fprintf(f, "required ");
      }
      fprintf(f, "string) default=%s\n", option._string.value);
      break;
    case opt_double:
      if(option._double.required){
        fprintf(f, "required ");
      }
      fprintf(f, "double) values=[%g, %g] default=%g\n", option._double.min, option._double.max, option._double.value);
      break;
    case opt_float:
      if(option._float.required){
        fprintf(f, "required ");
      }
      fprintf(f, "float) values=[%g, %g] default=%g\n", option._float.min, option._float.max, option._float.value);
      break;
    case opt_named:
      if(option._named.required){
        fprintf(f, "required ");
      }
      fprintf(f, "enum) values=[\n");
      {
        int i;
        for(i = 0; i < option._named.n_names - 1; i++){
          fprintf(f, "                      %-26s: %.30s\n", option._named.names[i], option._named.descs[i]);
        }
        fprintf(f, "                      %-26s: %-29s]\n", option._named.names[option._named.n_names-1], option._named.descs[option._named.n_names-1]);
      }
      break;
  }
}

static int opt_find_flag(int argc, char **argv, char *flag)
{
  int i;
  for( i = 1; i < argc; i++ )
    if( strcmp( argv[i], flag ) == 0 )
      return i;
  return -1;
}

void opt_show_option(opt_option option) {
  opt_fprintf_option(stdout, option);
}

void opt_eval_option(int argc, char **argv, opt_option *option){
  char flag[16];
  int i_flag;
  snprintf(flag, 16 * sizeof(char), "-%c", option->header.short_name);
  i_flag = opt_find_flag(argc, argv, flag);
  if(i_flag < 0){
    snprintf(flag, 16 * sizeof(char), "--%s", option->header.long_name);
    i_flag = opt_find_flag(argc, argv, flag);
  }
  switch(option->type){
    case opt_flag:
      option->_flag.exists = i_flag >= 0;
      break;
    case opt_int:
      if(i_flag >= 0){
        if(i_flag + 1 >= argc){
          fprintf(stderr, "error: option takes an argument\n");
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
        char *end;
        option->_int.value = (int)strtol(argv[i_flag + 1], &end, 0);
        if(end != argv[i_flag + 1] + strlen(argv[i_flag + 1])){
          fprintf(stderr, "error: invalid integer format %s\n", argv[i_flag + 1]);
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
        if(option->_int.value > option->_int.max || option->_int.value < option->_int.min){
          fprintf(stderr, "error: integer out of bounds %d\n", option->_int.value);
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
      }else{
        if(i_flag < 0 && option->_int.required){
          fprintf(stderr, "error: required argument not found\n");
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
      }
      break;
    case opt_string:
      if(i_flag >= 0){
        if(i_flag + 1 >= argc){
          fprintf(stderr, "error: option takes an argument\n");
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
        option->_string.value = argv[i_flag + 1];
      }else{
        if(i_flag < 0 && option->_string.required){
          fprintf(stderr, "error: required argument not found\n");
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
      }
      break;
    case opt_double:
      if(i_flag >= 0){
        if(i_flag + 1 >= argc){
          fprintf(stderr, "error: option takes an argument\n");
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
        char *end;
        option->_double.value = strtod(argv[i_flag + 1], &end);
        if(end != argv[i_flag + 1] + strlen(argv[i_flag + 1])){
          fprintf(stderr, "error: invalid double format %s\n", argv[i_flag + 1]);
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
        if(option->_double.value > option->_double.max || option->_double.value < option->_double.min){
          fprintf(stderr, "error: double out of bounds %f\n", option->_double.value);
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
      }else{
        if(i_flag < 0 && option->_double.required){
          fprintf(stderr, "error: required argument not found\n");
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
      }
      break;
    case opt_float:
      if(i_flag >= 0){
        if(i_flag + 1 >= argc){
          fprintf(stderr, "error: option takes an argument\n");
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
        char *end;
        option->_float.value = (float)strtod(argv[i_flag + 1], &end);
        if(end != argv[i_flag + 1] + strlen(argv[i_flag + 1])){
          fprintf(stderr, "error: invalid float format %s\n", argv[i_flag + 1]);
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
        if(option->_float.value > option->_float.max || option->_float.value < option->_float.min){
          fprintf(stderr, "error: float out of bounds %f\n", option->_float.value);
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
      }else{
        if(i_flag < 0 && option->_float.required){
          fprintf(stderr, "error: required argument not found\n");
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
      }
      break;
    case opt_named:
      if(i_flag >= 0){
        if(i_flag + 1 >= argc){
          fprintf(stderr, "error: option takes an argument\n");
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
        int i;
        for(i = 0; i < option->_named.n_names; i++){
          if(strcmp(option->_named.names[i], argv[i_flag + 1]) == 0){
            option->_named.value = i;
            return;
          }
        }
        fprintf(stderr, "error: invalid argument %s\n", argv[i_flag + 1]);
        opt_fprintf_option(stderr, *option);
        exit(125);
      }else{
        if(i_flag < 0 && option->_named.required){
          fprintf(stderr, "error: required argument not found\n");
          opt_fprintf_option(stderr, *option);
          exit(125);
        }
      }
      break;
  }
}
