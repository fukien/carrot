
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sql.tab.h"
#include "sql-parser.h"
#include "parser.h"
#include "../global.h"
#include "../common.h"

static const char *attr_names[] = {
	[SCA_NOTNULL]		= "SCA_NOTNULL",
	[SCA_DEF_STR]		= "SCA_DEF_STR",
	[SCA_DEF_NUM]		= "SCA_DEF_NUM",
	[SCA_DEF_FLOAT]		= "SCA_DEF_FLOAT",
	[SCA_DEF_BOOL]		= "SCA_DEF_BOOL",
	[SCA_AUTOINC]		= "SCA_AUTOINC",
	[SCA_UNIQUE_KEY]	= "SCA_UNIQUE_KEY",
	[SCA_PRIMARY_KEY]	= "SCA_PRIMARY_KEY",
	[SCA_COMMENT]		= "SCA_COMMENT",
};

static const char *op_names[] = {
	[SEO_ADD]	= "SEO_ADD",
	[SEO_SUB]	= "SEO_SUB",
	[SEO_MUL]	= "SEO_MUL",
	[SEO_DIV]	= "SEO_DIV",
	[SEO_MOD]	= "SEO_MOD",
	[SEO_NEG]	= "SEO_NEG",
	[SEO_AND]	= "SEO_AND",
	[SEO_OR]	= "SEO_OR",
	[SEO_XOR]	= "SEO_XOR",
	[SEO_BITOR]	= "SEO_BITOR",
	[SEO_BITAND]	= "SEO_BITAND",
	[SEO_BITXOR]	= "SEO_BITXOR",
	[SEO_SHIFT]	= "SEO_SHIFT",
	[SEO_NOT]	= "SEO_NOT",
	[SEO_ASSIGN]	= "SEO_ASSIGN",
	[SEO_IS_NULL]	= "SEO_IS_NULL",
	[SEO_SHR]	= "SEO_SHR",
	[SEO_SHL]	= "SEO_SHL",
	[SEO_BETWEEN]	= "SEO_BETWEEN",
	[SEO_EXISTS]	= "SEO_EXISTS",
	[SEO_IN_SELECT]	= "SEO_IN_SELECT",
	[SEO_LIKE]	= "SEO_LIKE",
	[SEO_REGEX]	= "SEO_REGEX",
	[SEO_STRTOBIN]	= "SEO_STRTOBIN",
};

static const char *interval_names[] = {
	[SDI_DAY_HOUR]		= "SDI_DAY_HOUR",
	[SDI_DAY_MICROSECOND]	= "SDI_DAY_MICROSECOND",
	[SDI_DAY_MINUTE]	= "SDI_DAY_MINUTE",
	[SDI_DAY_SECOND]	= "SDI_DAY_SECOND",
	[SDI_YEAR_MONTH]	= "SDI_YEAR_MONTH",
	[SDI_YEAR]		= "SDI_YEAR",
	[SDI_HOUR_MICROSECOND]	= "SDI_HOUR_MICROSECOND",
	[SDI_HOUR_MINUTE]	= "SDI_HOUR_MINUTE",
	[SDI_HOUR_SECOND]	= "SDI_HOUR_SECOND",
};

void removeFirstAndLast(char*des, char*src)
{
    for(int i = 1; i < strlen(src)-1; i++)
        {
            des[i-1] = src[i];
        }
            des[strlen(src)-1] = '\0';
}

void sqlp_alias(struct psql_state *pstate, const char *alias)
{
	printf("exec ALIAS %s\n", alias);
}

void sqlp_assign(struct psql_state *pstate, const char *db_name, const char *name)
{
    strcpy(uw.assWhere[uw.assCursor],name);
    uw.assType[uw.assCursor] = 26;
    uw.assCursor ++ ;
    uw.ass = 1;

	printf("exec ASSIGN %s%s%s\n",
	       db_name ? db_name : "",
	       db_name ? "." : "",
	       name);
}

void sqlp_assign_at(struct psql_state *pstate, const char *name)
{
	printf("exec ASSIGN-AT %s\n", name);
}

void sqlp_bool(struct psql_state *pstate, int val)
{
	printf("exec BOOL %d\n", val);
}

void sqlp_call(struct psql_state *pstate, int n_args, const char *name)
{
	printf("exec CALL %d %s\n", n_args, name);
}

void sqlp_call_date(struct psql_state *pstate, int n_args, enum sqlp_expr_ops op)
{
	printf("exec CALL %d DATE %s\n",
	       n_args,
	       op == SEO_ADD ? "ADD" : "SUB");
}

void sqlp_call_trim_opts(struct psql_state *pstate, int trim_opts)
{
	printf("exec CALL TRIM OPTS %d\n", trim_opts);
}

void sqlp_case(struct psql_state *pstate, int n_list, int have_else)
{
	printf("exec CASE %d %d\n", n_list, have_else);
}

void sqlp_caseval(struct psql_state *pstate, int n_list, int have_else)
{
	printf("exec CASEVAL %d %d\n", n_list, have_else);
}

void sqlp_col_attr(struct psql_state *pstate, enum sqlp_col_attribs attr)
{
	printf("exec ATTR %s\n", attr_names[attr]);
}

void sqlp_col_attr_uniq(struct psql_state *pstate, int n_cols)
{
	printf("exec ATTR UNIQUE-KEY %d\n", n_cols);
}

void sqlp_col_attr_comm(struct psql_state *pstate, const char *comm)
{
	printf("exec ATTR COMMENT %s\n", comm);
}

void sqlp_col_charset(struct psql_state *pstate, const char *charset)
{
	printf("exec ATTR CHARSET %s\n", charset);
}

void sqlp_col_collate(struct psql_state *pstate, const char *collate)
{
	printf("exec ATTR COLLATE %s\n", collate);
}

void sqlp_col_def_str(struct psql_state *pstate, const char *str)
{
	printf("exec ATTR DEFAULT-STR %s\n", str);
}

void sqlp_col_def_num(struct psql_state *pstate, int num)
{
	printf("exec ATTR DEFAULT-NUM %d\n", num);
}

void sqlp_col_def_float(struct psql_state *pstate, float num)
{
	printf("exec ATTR DEFAULT-FLOAT %g\n", num);
}

void sqlp_col_def_bool(struct psql_state *pstate, int bool)
{
	printf("exec ATTR DEFAULT-BOOL %d\n", bool);
}

void sqlp_col_key_pri(struct psql_state *pstate, int n_cols)
{
	printf("exec KEY-PRI %d\n", n_cols);
}

void sqlp_col_key(struct psql_state *pstate, int n_cols)
{
	printf("exec KEY %d\n", n_cols);
}

void sqlp_col_key_textidx(struct psql_state *pstate, int n_cols)
{
	printf("exec KEY-TEXTIDX %d\n", n_cols);
}

void sqlp_column(struct psql_state *pstate, const char *name)
{
	printf("exec COLUMN %s\n", name);
}

void sqlp_create_db(struct psql_state *pstate, int if_ne, const char *name)
{
	printf("exec CREATE-DB %d %s\n", if_ne, name);
}

void sqlp_create_sel(struct psql_state *pstate, int ignore_replace)
{
	printf("exec CREATE-SELECT %d\n", ignore_replace);
}

void sqlp_create_tbl(struct psql_state *pstate, int temp, int if_n_exists, int n_cols,
		     const char *db_name, const char *name)
{
    queryTree.query_type = 1;  // change the type to create
    strcpy(queryTree.tableList[queryTree.fromListNum].name, name);
	queryTree.tableList[queryTree.fromListNum].fieldNum = n_cols;
	for(int i = 0; i < mfcListCursor; i++)
    {
            queryTree.tableList[queryTree.fromListNum].mfc_list[i].dataTypeFlag= mfcList[i].dataTypeFlag;
            strcpy(queryTree.tableList[queryTree.fromListNum].mfc_list[i].fieldName,mfcList[i].fieldName);
            queryTree.tableList[queryTree.fromListNum].mfc_list[i].len=mfcList[i].len;
	}
	for(int i = 0; i < mfListCursor; i ++)
    {
            queryTree.tableList[queryTree.fromListNum].mf_list[i].dataTypeFlag= mfList[i].dataTypeFlag;
            strcpy(queryTree.tableList[queryTree.fromListNum].mf_list[i].fieldName,mfList[i].fieldName);
    }
	queryTree.fromListNum++;
	printf("exec CREATE-TABLE %d %d %d %s%s%s\n",
	       temp, if_n_exists, n_cols,
	       db_name ? db_name : "",
	       db_name ? "." : "",
	       name);
}

void sqlp_create_tbl_sel(struct psql_state *pstate, int temp, int if_n_exists, int n_cols,
		     const char *db_name, const char *name)
{
	printf("exec CREATE-TABLE-SELECT %d %d %d %s%s%s\n",
	       temp, if_n_exists, n_cols,
	       db_name ? db_name : "",
	       db_name ? "." : "",
	       name);
}

void sqlp_date_interval(struct psql_state *pstate, enum sqlp_date_intervals interval)
{
	printf("exec DATE-INTERVAL %s\n", interval_names[interval]);
}

void sqlp_def_col(struct psql_state *pstate, int flags, const char *name)
{
    Byte dataTypeFlag;
    int kilo = 0;
    int hun = 0;
    int isChar = 0;  // to identify if it is char(varchar) or not
    kilo = flags/1000;
    hun = flags%1000;
    switch (kilo)
    {
        case 50:
            dataTypeFlag = 0x03; // INTEGER
            break;
        case 80:
            dataTypeFlag = 0x06; // DOUBLE
            break;
        case 90:
            dataTypeFlag = 0x05;// FLOAT
            break;
        case 100:
            if (hun == 1)
                {
                    dataTypeFlag = 0x7 ;// DATE
                    dataTypeFlag = 0x01;// 强制更改DATE为CHAR型
                    hun = 16;//并设定长度为16
                    isChar = 1; //切记设定字符位
                }
            break;
        case 120:
            dataTypeFlag = 0x01; // CHAR;
            isChar = 1;
            break;
        case 130:
            dataTypeFlag = 0x02; // VARCHAR
            isChar = 1;
            break;
        default:
            break;
    }
    if(isChar)
    {
        mfcList[mfcListCursor].dataTypeFlag = dataTypeFlag;
        strcpy(mfcList[mfcListCursor].fieldName,name);
        mfcList[mfcListCursor].len = hun;
        mfcListCursor++;
    }else
    {
        mfList[mfListCursor].dataTypeFlag = dataTypeFlag;
        strcpy(mfList[mfListCursor].fieldName,name);
        mfListCursor ++;
    }
	printf("exec DEFINE-COL %d %s\n", flags, name);
}

void sqlp_delete(struct psql_state *pstate, int opts, const char *name)
{
    queryTree.query_type = 5;
    strcpy(dw.tableName, name);

	printf("exec DELETE %d %s\n", opts, name);
}

void sqlp_delete_multi(struct psql_state *pstate, int opts, int n_del, int n_tbl_ref)
{
	printf("exec DELETE-MULTI %d %d %d\n", opts, n_del, n_tbl_ref);
}

void sqlp_drop_db(struct psql_state *pstate, int if_exists, const char *name)
{
	printf("exec DROP-DB %d %s\n", if_exists, name);
}

void sqlp_drop_table(struct psql_state *pstate, int temp, int if_exists, int n_tables)
{
	queryTree.query_type = 2;
	printf("exec DROP-TABLE %d %d %d\n", temp, if_exists, n_tables);
}

void sqlp_enum_val(struct psql_state *pstate, const char *val)
{
	printf("exec ENUM-VAL %s\n", val);
}

void sqlp_expr_cmp(struct psql_state *pstate, int comp)
{
    char cmp[64];
    switch (comp)
    {
    case 1:
        strcat(cmp,"<");
        dw.type[dw.whereCursor] = 12;
        uw.type[uw.whereCursor] = 12;
        sw.type[sw.whereCursor] = 12;
        jw.type[jw.whereCursor] = 12;
        break;
    case 2:
        strcat(cmp,">");
        dw.type[dw.whereCursor] = 13;
        uw.type[uw.whereCursor] = 13;
        sw.type[sw.whereCursor] = 13;
        jw.type[jw.whereCursor] = 13;
        break;
    case 3:
        strcat(cmp,"!=");
        dw.type[dw.whereCursor] = 14;
        uw.type[uw.whereCursor] = 14;
        sw.type[sw.whereCursor] = 14;
        jw.type[jw.whereCursor] = 14;
        break;
    case 4:
        strcat(cmp,"=");
        dw.type[dw.whereCursor] = 15;
        uw.type[uw.whereCursor] = 15;
        sw.type[sw.whereCursor]= 15;
        jw.type[jw.whereCursor] = 15;
        break;
    case 24:
        strcat(cmp, "<=");
        dw.type[dw.whereCursor] = 24;
        uw.type[uw.whereCursor] = 24;
        sw.type[sw.whereCursor] = 24;
        jw.type[jw.whereCursor] = 24;
        break;
    case 25:
        strcat(cmp, ">=");
        dw.type[dw.whereCursor] = 25;
        uw.type[uw.whereCursor] = 25;
        sw.type[sw.whereCursor] = 25;
        jw.type[jw.whereCursor] = 25;
        break;
    default:
        break;
    }
    strcpy(dw.where[dw.whereCursor],cmp);
    dw.whereCursor++;

    strcpy(uw.where[uw.whereCursor],cmp);
    uw.whereCursor++;

    strcpy(sw.where[sw.whereCursor],cmp);
    sw.whereCursor++;

    strcpy(jw.where[jw.whereCursor], cmp);
    jw.whereCursor ++;

	printf("exec CMP %d\n", comp);
}

void sqlp_expr_is_bool(struct psql_state *pstate, int val)
{
	printf("exec EXPR-IS-BOOL %d\n", val);
}

void sqlp_expr_is_in(struct psql_state *pstate, int val)
{
	printf("exec EXPR-IS-IN %d\n", val);
}

void sqlp_expr_op(struct psql_state *pstate, enum sqlp_expr_ops op)
{
    strcpy(dw.where[dw.whereCursor], op_names[op]);
    switch(op)
    {
        case SEO_ADD:
            dw.type[dw.whereCursor] = 4;
            break;
        case SEO_SUB:
            dw.type[dw.whereCursor] = 5;
            break;
        case SEO_MUL:
            dw.type[dw.whereCursor] = 6;
            break;
        case SEO_DIV:
            dw.type[dw.whereCursor] = 7;
            break;
        case SEO_MOD:
            dw.type[dw.whereCursor] = 8;
            break;
        case SEO_AND:
            dw.type[dw.whereCursor] = 9;
            break;
        case SEO_OR:
            dw.type[dw.whereCursor] = 10;
            break;
        case SEO_NEG:
            dw.type[dw.whereCursor] = 16;
            break;
        case SEO_XOR:
            dw.type[dw.whereCursor] = 17;
            break;
        case SEO_NOT:
            dw.type[dw.whereCursor] = 18;
            break;
        case SEO_LIKE:
            dw.type[dw.whereCursor] = 19;
            break;
        case SEO_EXISTS:
            dw.type[dw.whereCursor] = 20;
            break;
        case SEO_IN_SELECT:
            dw.type[dw.whereCursor] = 21;
            break;
        case SEO_BETWEEN:
            dw.type[dw.whereCursor] = 22;
            break;
        case SEO_IS_NULL:
            dw.type[dw.whereCursor] = 23;
            break;
        case SEO_REGEX:
            dw.type[dw.whereCursor] = 24;
            break;
        default:
            break;
    }
    dw.whereCursor++;

       if(uw.ass == 1)
        {
            strcpy(uw.where[uw.whereCursor], op_names[op]);
                switch(op)
                {
                    case SEO_ADD:
                        uw.type[uw.whereCursor] = 4;
                        break;
                    case SEO_SUB:
                        uw.type[uw.whereCursor] = 5;
                        break;
                    case SEO_MUL:
                        uw.type[uw.whereCursor] = 6;
                        break;
                    case SEO_DIV:
                        uw.type[uw.whereCursor] = 7;
                        break;
                    case SEO_MOD:
                        uw.type[uw.whereCursor] = 8;
                        break;
                    case SEO_AND:
                        uw.type[uw.whereCursor] = 9;
                        break;
                    case SEO_OR:
                        uw.type[uw.whereCursor] = 10;
                        break;
                    case SEO_NEG:
                        uw.type[uw.whereCursor] = 16;
                        break;
                    case SEO_XOR:
                        uw.type[uw.whereCursor] = 17;
                        break;
                    case SEO_NOT:
                        uw.type[uw.whereCursor] = 18;
                        break;
                    case SEO_LIKE:
                        uw.type[uw.whereCursor] = 19;
                        break;
                    case SEO_EXISTS:
                        uw.type[uw.whereCursor] = 20;
                        break;
                    case SEO_IN_SELECT:
                        uw.type[uw.whereCursor] = 21;
                        break;
                    case SEO_BETWEEN:
                        uw.type[uw.whereCursor] = 22;
                        break;
                    case SEO_IS_NULL:
                        uw.type[uw.whereCursor] = 23;
                        break;
                    case SEO_REGEX:
                        uw.type[uw.whereCursor] = 24;
                        break;
                    default:
                        break;
                }
                uw.whereCursor++;
        }

         if(sw.isProj == 1)
        {
            strcpy(sw.where[sw.whereCursor], op_names[op]);
                switch(op)
                {
                    case SEO_ADD:
                        sw.type[sw.whereCursor] = 4;
                        break;
                    case SEO_SUB:
                        sw.type[sw.whereCursor] = 5;
                        break;
                    case SEO_MUL:
                        sw.type[sw.whereCursor] = 6;
                        break;
                    case SEO_DIV:
                        sw.type[sw.whereCursor] = 7;
                        break;
                    case SEO_MOD:
                        sw.type[sw.whereCursor] = 8;
                        break;
                    case SEO_AND:
                        sw.type[sw.whereCursor] = 9;
                        break;
                    case SEO_OR:
                        sw.type[sw.whereCursor] = 10;
                        break;
                    case SEO_NEG:
                        sw.type[sw.whereCursor] = 16;
                        break;
                    case SEO_XOR:
                        sw.type[sw.whereCursor] = 17;
                        break;
                    case SEO_NOT:
                        sw.type[sw.whereCursor] = 18;
                        break;
                    case SEO_LIKE:
                        sw.type[sw.whereCursor] = 19;
                        break;
                    case SEO_EXISTS:
                        sw.type[sw.whereCursor] = 20;
                        break;
                    case SEO_IN_SELECT:
                        sw.type[sw.whereCursor] = 21;
                        break;
                    case SEO_BETWEEN:
                        sw.type[sw.whereCursor] = 22;
                        break;
                    case SEO_IS_NULL:
                        sw.type[sw.whereCursor] = 23;
                        break;
                    case SEO_REGEX:
                        sw.type[sw.whereCursor] = 24;
                        break;
                    default:
                        break;
                }
                sw.whereCursor++;
        }

             if(jw.isProj == 1)
        {
            strcpy(jw.where[jw.whereCursor], op_names[op]);
                switch(op)
                {
                    case SEO_ADD:
                        jw.type[jw.whereCursor] = 4;
                        break;
                    case SEO_SUB:
                        jw.type[jw.whereCursor] = 5;
                        break;
                    case SEO_MUL:
                        jw.type[jw.whereCursor] = 6;
                        break;
                    case SEO_DIV:
                        jw.type[jw.whereCursor] = 7;
                        break;
                    case SEO_MOD:
                        jw.type[jw.whereCursor] = 8;
                        break;
                    case SEO_AND:
                        jw.type[jw.whereCursor] = 9;
                        break;
                    case SEO_OR:
                        jw.type[jw.whereCursor] = 10;
                        break;
                    case SEO_NEG:
                        jw.type[jw.whereCursor] = 16;
                        break;
                    case SEO_XOR:
                        jw.type[jw.whereCursor] = 17;
                        break;
                    case SEO_NOT:
                        jw.type[jw.whereCursor] = 18;
                        break;
                    case SEO_LIKE:
                        jw.type[jw.whereCursor] = 19;
                        break;
                    case SEO_EXISTS:
                        jw.type[jw.whereCursor] = 20;
                        break;
                    case SEO_IN_SELECT:
                        jw.type[jw.whereCursor] = 21;
                        break;
                    case SEO_BETWEEN:
                        jw.type[jw.whereCursor] = 22;
                        break;
                    case SEO_IS_NULL:
                        jw.type[jw.whereCursor] = 23;
                        break;
                    case SEO_REGEX:
                        jw.type[jw.whereCursor] = 24;
                        break;
                    default:
                        break;
                }
                jw.whereCursor++;
        }

	printf("exec EXPR-OP %s\n", op_names[op]);
}

void sqlp_expr_cmp_sel(struct psql_state *pstate, int sel_type, int comp)
{
	printf("exec CMP-SELECT %d %d\n", sel_type, comp);
}

void sqlp_fieldname(struct psql_state *pstate, const char *db_name, const char *name)
{
    if(jw.isProj == 0)
        {
            strcpy(jw.fieldList[jw.fieldNum], db_name);
            strcat(jw.fieldList[jw.fieldNum],".");
            strcat(jw.fieldList[jw.fieldNum], name);
            jw.fieldNum ++;
        }else
        {
            strcpy(jw.where[jw.whereCursor], db_name);
            strcat(jw.where[jw.whereCursor], ".");
            strcat(jw.where[jw.whereCursor],name);
            jw.type[jw.whereCursor] = 0;
            jw.whereCursor ++;
        }
	printf("exec FIELD-NAME %s.%s\n", db_name, name);
}

void sqlp_float(struct psql_state *pstate, float val)
{
    ttit.floatField[ttit.floatNum] = val;
    ttit.floatNum++;

    sprintf(dw.where[dw.whereCursor], "%f",val);
    dw.type[dw.whereCursor] = 2;
    dw.whereCursor ++;


    if(uw.ass == 0){
        sprintf(uw.assWhere[uw.assCursor], "%f", val);
        uw.assType[uw.assCursor] = 2;
        uw.assCursor ++;
    }else
    {
        sprintf(uw.where[uw.whereCursor],"%f", val);
        uw.type[uw.whereCursor] = 2;
        uw.whereCursor++;
    }

    if(sw.isProj == 1)
        {
            sprintf(sw.where[sw.whereCursor], "%f", val);
            sw.type[sw.whereCursor] = 2;
            sw.whereCursor ++;
        }

	printf("exec FLOAT %g\n", val);
}

void sqlp_group_by_list(struct psql_state *pstate, int n_list, int opts)
{
	printf("exec GROUPBY-LIST %d %d\n", n_list, opts);
}

void sqlp_group_by(struct psql_state *pstate, int opts)
{
	printf("exec GROUPBY %d\n", opts);
}

void sqlp_having(struct psql_state *pstate)
{
	printf("exec HAVING\n");
}

void sqlp_index(struct psql_state *pstate, const char *name)
{
	printf("exec INDEX %s\n", name);
}

void sqlp_index_hint(struct psql_state *pstate, int n_indexed, int opts)
{
	printf("exec INDEX-HINT %d %d\n", n_indexed, opts);
}

void sqlp_ins_cols(struct psql_state *pstate, int n_cols)
{
    printf("exec INSERT-COLS %d\n", n_cols);
}

void sqlp_ins_default(struct psql_state *pstate)
{
	printf("exec INSERT-DEFAULT\n");
}

void sqlp_ins_dup_update(struct psql_state *pstate, int n_assn)
{
	printf("exec INSERT DUP-ONUPDATE %d\n", n_assn);
}

void sqlp_insert(struct psql_state *pstate, int opts, int n_vals, const char *tbl_name)
{
    queryTree.query_type = 3;
    ttit.fieldNum= ttit.intNum + ttit.floatNum + ttit.stringNum;
    strcpy(ttit.tableName,tbl_name);
	printf("exec INSERT %d %d %s\n", opts, n_vals, tbl_name);
}

void sqlp_insert_assn(struct psql_state *pstate, int opts, int n_assn, const char *tbl_name)
{
	printf("exec INSERT-ASSN %d %d %s\n", opts, n_assn, tbl_name);
}

void sqlp_insert_sel(struct psql_state *pstate, int opts, const char *tbl_name)
{
	printf("exec INSERT-SEL %d %s\n", opts, tbl_name);
}

void sqlp_into(struct psql_state *pstate, int n_cols)
{
	printf("exec INTO %d\n", n_cols);
}

void sqlp_join(struct psql_state *pstate, int opts)
{
	printf("exec JOIN %d\n", opts);
}

void sqlp_join_expr(struct psql_state *pstate)
{
	printf("exec JOIN-ON EXPR\n");
}

void sqlp_join_using(struct psql_state *pstate, int n_cols)
{
	printf("exec JOIN-USING %d\n", n_cols);
}

void sqlp_limit(struct psql_state *pstate, int two_expr)
{
	printf("exec LIMIT %d\n", two_expr);
}

void sqlp_name(struct psql_state *pstate, const char *name)
{
    strcpy(dw.where[dw.whereCursor], name);
    dw.type[dw.whereCursor] = 0;
    dw.whereCursor++;

    if(uw.ass == 1)
        {
            strcpy(uw.where[uw.whereCursor], name);
            uw.type[uw.whereCursor] = 0;
            uw.whereCursor++;
        }

    if(sw.isProj == 0)
    {
        strcpy(sw.fieldList[sw.fieldNum], name);
        sw.fieldNum++;
    }else
    {
        strcpy(sw.where[sw.whereCursor],name);
        sw.type[sw.whereCursor] = 0;
        sw.whereCursor++;
    }

	printf("exec NAME %s\n", name);
}

void sqlp_now(struct psql_state *pstate)
{
	printf("exec NOW\n");
}

void sqlp_number(struct psql_state *pstate, int val)
{
    ttit.intField[ttit.intNum] = val;
    ttit.intNum++;

    sprintf(dw.where[dw.whereCursor],"%d", val);
    dw.type[dw.whereCursor] = 1;
    dw.whereCursor++;

    if(uw.ass == 0){
        sprintf(uw.assWhere[uw.assCursor], "%d", val);
        uw.assType[uw.assCursor] = 1;
        uw.assCursor ++;
    }else
    {
        sprintf(uw.where[uw.whereCursor],"%d", val);
        uw.type[uw.whereCursor] = 1;
        uw.whereCursor++;
    }

    if(sw.isProj == 1)
        {
            sprintf(sw.where[sw.whereCursor], "%d", val);
            sw.type[sw.whereCursor] = 1;
            sw.whereCursor ++;
        }

    printf("exec INT/NUMBER %d\n", val);
}

void sqlp_order_by(struct psql_state *pstate, int n_list)
{
	printf("exec ORDER-BY %d\n", n_list);
}

void sqlp_replace_assn(struct psql_state *pstate, int opts, int n_assn, const char *name)
{
	printf("exec REPLACE-ASSN %d %d %s\n", opts, n_assn, name);
}

void sqlp_replace_vals(struct psql_state *pstate, int opts, int n_vals, const char *name)
{
	printf("exec REPLACE-VALS %d %d %s\n", opts, n_vals, name);
}

void sqlp_replace_sel(struct psql_state *pstate, int opts, const char *name)
{
	printf("exec REPLACE-SEL %d %s\n", opts, name);
}

void sqlp_select(struct psql_state *pstate, int opts, int n_expr, int n_tbl_ref)
{
    queryTree.query_type = 6;
    if(n_tbl_ref>1)
        {
            queryTree.query_type = 7; // A MARK FOR JOIN IDENTIFICATION
        }
	printf("exec SELECT %d %d %d\n", opts, n_expr, n_tbl_ref);

}

void sqlp_select_nodata(struct psql_state *pstate, int opts, int n_expr)
{
	printf("exec SELECT-NODATA %d %d\n", opts, n_expr);
}

void sqlp_select_all(struct psql_state *pstate)
{
    sw.isAll = 1;
    jw.isAll = 1;
	printf("exec SELECT-ALL\n");
}

void sqlp_set(struct psql_state *pstate, const char *name)
{
	printf("exec SET %s\n", name);
}

void sqlp_start_col(struct psql_state *pstate)
{
	printf("exec START-COL\n");
}

void sqlp_stmt(struct psql_state *pstate)
{
	printf("exec STMT\n");
	//printf("\nYES WE ARE CARROTS !!!\n\n");
}

void sqlp_string(struct psql_state *pstate, const char *str)
{
    //strcpy(ttit.stringField[ttit.stringNum],str);
    removeFirstAndLast(ttit.stringField[ttit.stringNum],str);
    //printf("ORIGINAL\t%s\n", str);
    //printf("NOW\t%s\n",ttit.stringField[ttit.stringNum]);
    ttit.stringNum++;

    removeFirstAndLast(dw.where[dw.whereCursor],str);
    dw.type[dw.whereCursor] = 3;
    dw.whereCursor++;


    if(uw.ass == 0){
        removeFirstAndLast(uw.assWhere[uw.assCursor], str);
        uw.assType[uw.assCursor] = 3;
        uw.assCursor ++;
    }else
    {
        removeFirstAndLast(uw.where[uw.whereCursor], str);
        uw.type[uw.whereCursor] = 3;
        uw.whereCursor++;
    }

    if(sw.isProj == 1)
        {
            removeFirstAndLast(sw.where[sw.whereCursor],str);
            sw.type[sw.whereCursor] = 3;
            sw.whereCursor ++;
        }

	printf("exec STRING %s\n", str);
}

void sqlp_subquery(struct psql_state *pstate)
{
	printf("exec SUBQUERY\n");
}

void sqlp_subquery_as(struct psql_state *pstate, const char *name)
{
	printf("exec SUBQUERY-AS %s\n", name);
}

void sqlp_table(struct psql_state *pstate, const char *db_name, const char *name)
{
    char dir[64] = "workspace/";
    strcat(dir,name);
    strcat(dir,".tb");
    ctfp.currentFp = fopen(dir,"r");
    strcpy(ctfp.name, dir);

    strcpy(uw.tableName,dir);

    strcpy(sw.tableName,dir);
    sw.isProj = 1;


    strcpy(jw.tableList[jw.tableCursor],name);
    jw.tableCursor ++;
    jw.isProj = 1;

    /*
    if(currentFp != NULL)
        {
            printf("YYYYYYYYY\n");
        }else
        {
            printf("NNNNNNNNNNNN\n");
        }
        */
	printf("exec TABLE %s%s%s\n",
	       db_name ? db_name : "",
	       db_name ? "." : "",
	       name);
}

void sqlp_table_refs(struct psql_state *pstate, int n_refs)
{
	printf("exec TABLE-REFERENCES %d\n", n_refs);
}

void sqlp_update(struct psql_state *pstate, int opts, int n_tbl_ref, int n_assn)
{
    queryTree.query_type = 4;
	printf("exec UPDATE %d %d %d\n", opts, n_tbl_ref, n_assn);
}

void sqlp_uservar(struct psql_state *pstate, const char *str)
{
	printf("exec USER-VAR %s\n", str);
}

void sqlp_values(struct psql_state *pstate, int n_vals)
{
	printf("exec VALUES %d\n", n_vals);
}

void sqlp_where(struct psql_state *pstate)
{
    strcpy(dw.where[dw.whereCursor], "WHERE");
    dw.type[dw.whereCursor] = 11;
    dw.whereCursor++;

    strcpy(uw.where[uw.whereCursor],"WHERE");
    uw.type[uw.whereCursor] = 11;
    uw.whereCursor++;

    strcpy(sw.where[sw.whereCursor],"WHERE");
    sw.type[sw.whereCursor] = 11;
    sw.whereCursor++;

    strcpy(jw.where[jw.whereCursor], "WHERE");
    jw.type[jw.whereCursor] = 11;
    jw.whereCursor ++;

	printf("exec WHERE\n");
}

