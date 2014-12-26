#!/usr/bin/perl

# +============================+
# | DX..Logger 2.0 Code Gen    |
# |(C)0DE black_ninja          |
# +============================+
# b14ck_n1nj4


#if ($ARGV==0){
#  print "Command line: sss.pl PFN23_ IDirect3DResource9 res9.txt\n";
#  exit;
#}

#$infile = shift @ARGV;
$infile="in.txt";

$outfile = $infile.".out.txt";

open(OUT,">$outfile") 	|| die "Can't open output file: $outfile\n";
open(IN,"<$infile")     || die "Can't open input file: $infile\n";

$idx = 0;
$NotFirst = 0;
$interf = "";
while ($s = <IN>){
	  $s =~ /#define (.+?)\((.*?)\).*$/;
	  $p = scalar(split(/,/,$2)); #Params count
	  
	  if($NotFirst == 0){
	      @z = split("_", $1);
		  $interf = $z[0];
		  printf OUT "FUNCDATA table_".$interf."[]={\n";
	      $NotFirst = 1;
	  }
	  
#{"IDirect3D9_QueryInterface",3},//0
#{"IDirect3D9_AddRef",1},//1 
	  printf OUT "\t{\"$1\",$p},//$idx\n";
	  $idx++;  
}
printf OUT "};\n";


printf OUT "void Hook_$interf(DWORD* p){\
	static int fNotFirst = 0;\
\
	if(!fNotFirst){\
		fNotFirst = 1;\
		for(DWORD i = 0; i < $idx; i++){\
			SFUNCTION finfo={0};\
			if(i==0){\
				finfo.BeforeFunc = (PPLUG_BEFORE)before_IUnknown_QueryInterface;\
			}\
\
			DWORD MethodAddress = GetMethodAddr((DWORD**)*p, i);\
			finfo.pName = table_".$interf."[i].pName;\
			finfo.params= table_".$interf."[i].Params;\
			SetHook(MethodAddress, &finfo);\
		}\
	}\
}\
";


close(IN);
close (OUT);
