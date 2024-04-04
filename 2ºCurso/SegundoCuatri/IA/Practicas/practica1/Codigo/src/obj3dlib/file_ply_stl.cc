//******************************************************************************
// class to read ply files of triangles
//
// Domingo Martín Perandres (c) 2003-2013
//
// Gnu Public Licence
//******************************************************************************

#include "obj3dlib/file_ply_stl.h"

//******************************************************************************
//
//******************************************************************************


_file_ply::_file_ply()
{
_element_token_table Element1;
const char* Text_tokens[]={"ply","format","ascii","element","vertex","face","end_header","zzzzzzzz",""};

for (int i=0;i<_tokens(NUMBER);i++)
	{
	Element1.Text=Text_tokens[i];
	Element1.Token=(_tokens) i;
	Token_table.push_back(Element1);
	}

Debug=false;
Buffer[0]='\0';
Num_lines=0;
}

//******************************************************************************
//
//******************************************************************************

int _file_ply::open(char *File_name)
{

if ((File=fopen(File_name,"r"))==NULL)
	{
	printf("Error: the file %s cannot be opened\n",File_name);
	return(-1);
	}
return(0);
}

//******************************************************************************
//
//******************************************************************************

int _file_ply::create(char *File_name)
{

if ((File=fopen(File_name,"w"))==NULL)
	{
	printf("Error: the file %s cannot be created\n",File_name);
	return(-1);
	}
return(0);
}

//******************************************************************************
//
//******************************************************************************

int _file_ply::read_line()
{


if (!feof(File))
	{
	fgets(Buffer,MAX_LENGTH_LINE,File);
	if (strlen(Buffer)==0) return(-1);
	Num_lines++;
	//printf("%d:%s",Num_lines,Buffer);
	return(0);
	}
return(-1);
}

//******************************************************************************
//
//******************************************************************************

int _file_ply::next_token()
{
char *p1,*p2;
char Aux_token[100];
int Num_char;

do
	{
	if (strlen(Buffer)==0)
		{
		if (read_line()==-1) return(-1);
		while (Buffer[0]=='#') if (read_line()==-1) return(-1);
		}
	p1=Buffer;
	while ((*p1==' ' || *p1=='\t') && *p1!='\n') p1++;
	p2=p1;
	while (*p2!=' ' && *p2!='\t' && *p2!='\n') p2++;
	Num_char=p2-p1;
	if (Num_char>99)
		{
		error("number of characters for token is too long\n");
		return(-1);
		}
	if (Num_char!=0)
		{
		strncpy(Aux_token,p1,Num_char);
		Aux_token[Num_char]='\0';
		}
	if (*p2=='\n') Buffer[0]='\0';
	else strcpy(Buffer,p2);
	}
while (Num_char==0);

if (!is_number(Aux_token))
	{
	//printf("es un numero %s\n",Aux_token);
	Yylval.Real=atof(Aux_token);
	return((int)_tokens(NUMBER));
	}
else
	{
	//printf("es texto %s\n",Aux_token);
	Yylval.Text=Aux_token;
	return(search_token(Aux_token));
	}
}

//******************************************************************************
//
//******************************************************************************

int _file_ply::
read(vector<float> &Vertices,vector<unsigned int> &Faces)
{
int Next_token,i,j;
int Num_vertices,Num_faces;

if (File!=NULL)
	{
	Next_token=next_token();
	if (Next_token==PLY)
		{
		Next_token=next_token();
		if (Next_token==FORMAT)
			{
			Next_token=next_token();
			if (Next_token==ASCII)
				{
				Next_token=next_token();
				if (Next_token==NUMBER)
					{// head
					Next_token=next_token();
					while (Next_token!=END_HEADER)
						{
						if (Next_token==ELEMENT)
							{
							Next_token=next_token();
							switch (Next_token)
								{
								case VERTEX:
									Next_token=next_token();
									if (Next_token==NUMBER)
										{
          					Num_vertices=(int) Yylval.Real;
										Vertices.resize(Num_vertices*3);
										}
									else error("no number of vertex");
									break;
								case FACE:
									Next_token=next_token();
									if (Next_token==NUMBER)
										{
          					Num_faces=(int) Yylval.Real;
										Faces.resize(Num_faces*3);
										}
									else error("no number of faces");
									break;
								default:
									error("element type not supported");
									break;
								}
							}
						Next_token=next_token();
						}
					// data
					// vertices data
					for (i=0;i<Num_vertices;i++)
						{// vertices data
						for (j=0;j<3;j++)
							{
							Next_token=next_token();
							if (Next_token==NUMBER)
								{
								Vertices[i*3+j]=Yylval.Real;
								}
							else error("no number for coordinate");
							}
						}
					// faces data
					for (i=0;i<Num_faces;i++)
						{
						Next_token=next_token();
						if (Next_token==NUMBER)
							{
							if ((int)Yylval.Real!=3) {
								printf("Face=%d Token=%s\n",i,Yylval.Text.c_str());
								error("only triangles supported");;
								}
							}
						else error("no number of vertex indices");
						for (j=0;j<3;j++)
							{
							Next_token=next_token();
							if (Next_token==NUMBER)
								{
								Faces[i*3+j]=(int)Yylval.Real;
								}
							else error("no number for coordinate");
							}
						}
					//printf("File readed\n");
					}
				else error("no format number");
				}
			else error("no ascii format");
			}
		else error("no format word");
		}
	else error("this is not a ply file");
	return(0);
	}
else
	{
	error("there is not a ply file open");
	return(-1);
	}
}

//******************************************************************************
//
//******************************************************************************

//int _file_ply::write(vector<float> &Vertices,vector<int> &Faces)
//{
//    error("Not implemented");
//    return(0);
//}

//******************************************************************************
//
//******************************************************************************

int _file_ply::close()
{

fclose(File);
return(0);
}

//******************************************************************************
//
//******************************************************************************

void _file_ply::error(const char *Error)
{

printf("Error: %s. Stop in line %d\n",Error,Num_lines);
exit(-1);
}

//******************************************************************************
//
//******************************************************************************

int _file_ply::is_number(char *Aux_token)
{
char *p1;

for (unsigned int i=0;i<strlen(Aux_token);i++)
	{
    if ((p1=strchr((char *)"0123456789.+-eE",Aux_token[i]))==NULL) return(-1);
	}
return(0);
}

//******************************************************************************
//
//******************************************************************************

int _file_ply::search_token(char *Aux_token)
{
int i=0;

while (!(Token_table[i].Text=="zzzzzzzz"))
	{
	//printf("Buscando token %d %s\n",i,Token_table[i].Text.c_str());
	if (Token_table[i].Text==Aux_token) break;
	i++;
	}
//getchar();
return(i);
}
