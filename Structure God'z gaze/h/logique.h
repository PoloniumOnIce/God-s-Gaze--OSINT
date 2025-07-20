#pragma once
#include <windows.h>
#include <string>

// Fonctions métier / logique
bool CreateResultFolderAndFile(const std::wstring& searchTerm, const std::wstring& basePath, const std::wstring& content);
std::wstring GetDefaultSavePath();  // Par défaut Bureau ou chemin défini par utilisateur
void SetSavePath(const std::wstring& newPath);

std::wstring GenerateResultContentForPseudo(const std::wstring& pseudo);
std::wstring GenerateResultContentForIP(const std::wstring& ip);
std::wstring GenerateResultContentForEmail(const std::wstring& email);

void LaunchSearchPseudo(const std::wstring& pseudo);
void LaunchSearchIP(const std::wstring& ip);
void LaunchSearchEmail(const std::wstring& email);

// Fonctions utilitaires
bool FolderExists(const std::wstring& path);
bool CreateFolder(const std::wstring& path);
bool WriteTextFile(const std::wstring& filePath, const std::wstring& content);