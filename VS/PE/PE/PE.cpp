// PE.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
//#include<cstring>
size_t t1 = 0;
size_t header = 0;
LPVOID DaK(LPSTR Fname)
{
	FILE* fp = NULL;
	errno_t err = 0;
	LPVOID DTnc = NULL;
	DWORD fsize = 0;
	err= fopen_s(&fp,Fname, "rb");
	if (err!=0)
	{
		printf("���ļ�ʧ��\n");
		return NULL;
	}
	fseek(fp, 0l, SEEK_END);
	fsize = ftell(fp);
	printf("�ļ���С:%d\n", fsize);
	DTnc = malloc(fsize);
	if (!DTnc)
	{
		printf("�����ڴ�ʧ��\n");
		return NULL;
	}
	fseek(fp, 0l, SEEK_SET);
	size_t	n = fread(DTnc, 1,fsize , fp);
	printf("�����С: %d\n", n);
	if (!n)
	{
		printf("��ȡ�ļ�ʧ��\n");
		free(DTnc);
		fclose(fp);
		return NULL;
	}
	//�ر��ļ�
	fclose(fp);
	return DTnc;

}
void OpenPeFile()
{
	LPVOID PeBufeer = NULL;
	PIMAGE_DOS_HEADER DosHeader = NULL;
	PIMAGE_NT_HEADERS NtHeader = NULL;
	PIMAGE_FILE_HEADER File_Header = NULL;
	PIMAGE_OPTIONAL_HEADER32 OptionalHeadear32 = NULL;
	PIMAGE_SECTION_HEADER SectionHearder = NULL;
	PeBufeer = DaK("c:\\1.exe");
	if (!PeBufeer)
	{
		printf("�ļ���ȡʧ��\n");
		return;
	}
	//�ж�DOSͷ
	if (*((PWORD)PeBufeer)!=IMAGE_DOS_SIGNATURE)
	{
		printf("������Ч��PE�ļ�\n");
		free(PeBufeer);
		return;
	}
	DosHeader = (PIMAGE_DOS_HEADER)PeBufeer;
	//��ӡDOSͷ
	printf("************************DOSHeader***********************\n");
	printf("e_magic  %x\n", DosHeader->e_magic);
	printf("e_cblp  %x\n", DosHeader->e_cblp);
	printf("e_cp  %x\n", DosHeader->e_cp);
	printf("e_crlc  %x\n", DosHeader->e_crlc);
	printf("e_cparhdr  %x\n", DosHeader->e_cparhdr);
	printf("e_minalloc  %x\n", DosHeader->e_minalloc);
	printf("e_maxalloc  %x\n", DosHeader->e_maxalloc);
	printf("e_ss  %x\n", DosHeader->e_ss);
	printf("e_sp  %x\n", DosHeader->e_sp);
	printf("e_csum  %x\n", DosHeader->e_csum);
	printf("e_ip  %x\n", DosHeader->e_ip);
	printf("e_cs  %x\n", DosHeader->e_cs);
	printf("e_lfarlc  %x\n", DosHeader->e_lfarlc);
	printf("e_ovno  %x\n", DosHeader->e_ovno);
	printf("e_res[4]  %x\n", DosHeader->e_res);
	printf("e_oemid  %x\n", DosHeader->e_oemid);
	printf("e_oeminfo  %x\n", DosHeader->e_oeminfo);
	printf("e_res2[10]  %x\n", DosHeader->e_res2);
	printf("e_lfanew  %x\n", DosHeader->e_lfanew);
	printf("***********************DOSend**************************\n");
	//�ж�NTͷ
	if (*((PDWORD)((DWORD)PeBufeer+DosHeader->e_lfanew))!=IMAGE_NT_SIGNATURE)
	{
		printf("������Ч��PE��־\n");
		free(PeBufeer);
		return;
	}
	printf("PeBufeer :%x\n", (DWORD)PeBufeer);
	NtHeader = (PIMAGE_NT_HEADERS)((DWORD)PeBufeer + DosHeader->e_lfanew);
	//��ӡNTͷ
	printf("*****************************NTheader******************\n");
	printf("Signature %x\n", NtHeader->Signature);
	printf("****************************NTend*********************\n");
	File_Header = (PIMAGE_FILE_HEADER)(((DWORD)NtHeader) + 4);
	//��ӡPEͷ
	printf("****************************PEheader*******************\n");
	printf("Machine %x\n", File_Header->Machine);
	printf("NumberOfSections %x\n", File_Header->NumberOfSections);
	printf("TimeDateStamp %x\n", File_Header->TimeDateStamp);
	printf("PointerToSymbolTable %x\n", File_Header->PointerToSymbolTable);
	printf("NumberOfSymbols %x\n", File_Header->NumberOfSymbols);
	printf("SizeOfOptionalHeader %x\n", File_Header->SizeOfOptionalHeader);
	printf("Characteristics %x\n", File_Header->Characteristics);
	//��ѡPEͷ
	OptionalHeadear32 = (PIMAGE_OPTIONAL_HEADER32)((DWORD)File_Header + IMAGE_SIZEOF_FILE_HEADER);
	//��ӡ��ѡPEͷ
	printf("******************************OPTIONALHEADER******************\n");
	printf("Magic %x\n", OptionalHeadear32->Magic);
	printf("MajorLinkerVersion %x\n", OptionalHeadear32->MajorLinkerVersion);
	printf("MinorLinkerVersion %x\n", OptionalHeadear32->MinorLinkerVersion);
	printf("SizeOfCode %x\n", OptionalHeadear32->SizeOfCode);
	printf("SizeOfInitializedData %x\n", OptionalHeadear32->SizeOfInitializedData);
	printf("SizeOfUninitializedData %x\n", OptionalHeadear32->SizeOfUninitializedData);
	printf("AddressOfEntryPoint %x\n", OptionalHeadear32->AddressOfEntryPoint);
	printf("BaseOfCode %x\n", OptionalHeadear32->BaseOfCode);
	printf("BaseOfData %x\n", OptionalHeadear32->BaseOfData);
	printf("ImageBase %x\n", OptionalHeadear32->ImageBase);
	printf("SectionAlignment %x\n", OptionalHeadear32->SectionAlignment);
	printf("FileAlignment %x\n", OptionalHeadear32->FileAlignment);
	printf("MajorOperatingSystemVersion %x\n", OptionalHeadear32->MajorOperatingSystemVersion);
	printf("MinorOperatingSystemVersion %x\n", OptionalHeadear32->MinorOperatingSystemVersion);
	printf("MajorImageVersion %x\n", OptionalHeadear32->MajorImageVersion);
	printf("MinorImageVersion %x\n", OptionalHeadear32->MinorImageVersion);
	printf("MajorSubsystemVersion %x\n", OptionalHeadear32->MajorSubsystemVersion);
	printf("MinorSubsystemVersion %x\n", OptionalHeadear32->MinorSubsystemVersion);
	printf("Win32VersionValue %x\n", OptionalHeadear32->Win32VersionValue);
	printf("SizeOfImage %x\n", OptionalHeadear32->SizeOfImage);
	t1 = OptionalHeadear32->SizeOfImage;
	header = OptionalHeadear32->SizeOfHeaders;
	printf("SizeOfHeaders %x\n", OptionalHeadear32->SizeOfHeaders);
	printf("CheckSum %x\n", OptionalHeadear32->CheckSum);
	printf("Subsystem %x\n", OptionalHeadear32->Subsystem);
	printf("DllCharacteristics %x\n", OptionalHeadear32->DllCharacteristics);
	printf("SizeOfStackReserve %x\n", OptionalHeadear32->SizeOfStackReserve);
	printf("SizeOfStackCommit %x\n", OptionalHeadear32->SizeOfStackCommit);
	printf("SizeOfHeapReserve %x\n", OptionalHeadear32->SizeOfHeapReserve);
	printf("SizeOfHeapCommit %x\n", OptionalHeadear32->SizeOfHeapCommit);
	printf("LoaderFlags %x\n", OptionalHeadear32->LoaderFlags);
	printf("NumberOfRvaAndSizes %x\n", OptionalHeadear32->NumberOfRvaAndSizes);
	printf("DataDirectory[16] %x\n", OptionalHeadear32->DataDirectory);
	printf("******************************OptionalEnd******************\n");
	printf("******************************�ڱ�ʼ******************\n");
	int Js = 0,i=0;
	Js = File_Header->NumberOfSections;
	SectionHearder = (PIMAGE_SECTION_HEADER)((DWORD)OptionalHeadear32 + File_Header->SizeOfOptionalHeader);
	printf("%d\n", Js);
	for (i = 0; i < Js;i++)
	{
		PIMAGE_SECTION_HEADER SectionHearderTemp = (PIMAGE_SECTION_HEADER)((DWORD)SectionHearder + (DWORD)(i*sizeof(_IMAGE_SECTION_HEADER)));
		char Sname[9] = { 0 };
		memcpy(Sname, SectionHearderTemp->Name, sizeof(Sname));
		printf("Name:                        [����:%s\t] \n", Sname);
		printf("Misc:                        [����:0x%0.8X\t] \n", SectionHearderTemp->Misc.PhysicalAddress);
		printf("VirtualAddress:              [����:0x%0.8X\t] \n", SectionHearderTemp->VirtualAddress);
		printf("SizeOfRawData:               [����:0x%0.8X\t] \n", SectionHearderTemp->SizeOfRawData);
		printf("PointerToRawData:            [����:0x%0.8X\t] \n", SectionHearderTemp->PointerToRawData);
		printf("PointerToRelocations:        [����:0x%0.8X\t] \n", SectionHearderTemp->PointerToRelocations);
		printf("PointerToLinenumbers:        [����:0x%0.8X\t] \n", SectionHearderTemp->PointerToLinenumbers);
		printf("NumberOfRelocations:         [����:0x%0.4X\t] \n", SectionHearderTemp->NumberOfRelocations);
		printf("NumberOfLinenumbers:         [����:0x%0.4X\t] \n", SectionHearderTemp->NumberOfLinenumbers);
		printf("Characteristics:             [����:0x%0.8X\t] \n", SectionHearderTemp->Characteristics);
	}
	printf("******************************�ڱ����******************\n");

}
void FileBuffer(size_t i)
{
	LPVOID PFile = NULL;
	LPVOID Tpy = NULL;
	Tpy = (LPVOID)malloc(i);
	PFile = DaK("c:\\1.exe");
	memcpy(Tpy, PFile, header);
}
int main()
{
	/*OpenPeFile();*/
	LPVOID TX = DaK("c:\\1.exe");
	getchar();
    return 0;
}

