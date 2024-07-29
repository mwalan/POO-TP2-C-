// #include "Reports.hpp"
// #include "Qualis.hpp"
// #include <fstream>
// #include <iomanip>
// #include <filesystem>
// #include <algorithm>

// namespace fs = std::filesystem;

// const string Reports::RECREDENCIAMENTO = "/1-recredenciamento.csv";
// const string Reports::PUBLICACOES = "/2-publicacoes.csv";
// const string Reports::ESTATISTICAS = "/3-estatisticas.csv";

// void Reports::writeRelatorios(const string& diretorio, const vector<int>& dataRecredenciamento,PPGI& ufes) {
//     createRelatorios(diretorio);
//     writeRecredenciamento(diretorio, dataRecredenciamento, ufes);
//     writePublicacoes(diretorio, ufes);
//     writeEstatisticas(diretorio, ufes);
// }

// void Reports::createRelatorios(const string& diretorio) {
//     fs::path saidaDir(diretorio + "/saida");
//     try {
//         if (!fs::exists(saidaDir)) {
//             fs::create_directories(saidaDir);
//         }

//         fs::path recredenciamentoPath(saidaDir / "1-recredenciamento.csv");
//         fs::path publicacoesPath(saidaDir / "2-publicacoes.csv");
//         fs::path estatisticasPath(saidaDir / "3-estatisticas.csv");

//         if (!fs::exists(recredenciamentoPath)) {
//             fs::create_directories(recredenciamentoPath);
//         }
//         if (!fs::exists(publicacoesPath)) {
//             fs::create_directories(publicacoesPath);
//         }
//         if (!fs::exists(estatisticasPath)) {
//             fs::create_directories(estatisticasPath);
//         }

//     } catch (const fs::filesystem_error& e) {
//         throw runtime_error("Erro ao criar arquivos de relatório: " + string(e.what()));
//     }
// }

// void Reports::writeRecredenciamento(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes) {
//     ofstream arquivo(diretorio + RECREDENCIAMENTO);

//     if (!arquivo.is_open()) {
//         throw runtime_error("Erro ao abrir o arquivo " + diretorio + RECREDENCIAMENTO);
//     }

//     arquivo << "Docente;Pontuação;Recredenciado?\n";

//     int anoRecredenciamento = dataRecredenciamento[2]; 

//     Regra regra = ufes.get_regra();
//     auto qualisPontos = regra.getQualisPontos();
//     auto periodicosNecessarios = regra.getPeriodicosNecessarios();
//     int quantidadePeriodicosNecessarios = regra.getQuantidadePeriodicosNecessarios();

//     /// corrigir isso

//     /// onde escrevo os docentes do departamento??
//     vector<Docente> docentes = ufes.get_docentes();

//     // Ordenar docentes por nome
//     sort(docentes.begin(), docentes.end(), [](Docente& a,Docente& b) {
//         return a.get_nome() < b.get_nome();
//     });

//     for (const auto& docente : docentes) {
//         double pontos = 0;
//         for (Publicacao & publicacao : docente.get_publicacoes()) {
//             int anoPublicacao = publicacao.get_ano();
//             if (anoRecredenciamento - anoPublicacao <= regra.getAnosPontos() &&
//                 anoPublicacao < anoRecredenciamento) {
//                 string qualis = publicacao.get_veiculo().getQualis()->getValor();
//                 pontos += qualisPontos.at(qualis);
//             }
//         }

//         int quantidade = 0;
//         for (Publicacao &publicacao : docente.get_publicacoes()) {
//             int anoPublicacao = publicacao.get_ano();
//             if (anoRecredenciamento - anoPublicacao <= regra.getAnosPeriodicos() &&
//                 anoPublicacao < anoRecredenciamento &&
//                 publicacao.get_veiculo().getTipo() == "P") {
//                 string qualis = publicacao.get_veiculo()->getQualis()->getValor();
//                 if (find(periodicosNecessarios.begin(), periodicosNecessarios.end(),
//                          qualis) != periodicosNecessarios.end()) {
//                     quantidade++;
//                 }
//             }
//         }

//         vector<int> dataIngresso = docente.get_data_ingresso();
//         int diaIngresso = dataIngresso[0];
//         int mesIngresso = dataIngresso[1];
//         int diffIngresso = anoRecredenciamento - dataIngresso[2];

//         auto dataNascimento = docente.get_data_nascimento();
//         int diffNascimento = anoRecredenciamento - dataNascimento[2];

//         string recredenciado = "Não";

//         if (docente.is_bolsista()) {
//             recredenciado = "Bolsista CNPq";
//         } else if (docente.is_coordenador()) {
//             recredenciado = "Coordenador";
//         } else if (docente.is_licenciado()) {
//             recredenciado = "Licença Maternidade";
//         } else if (diffIngresso < 2 || (diffIngresso == 2 && mesIngresso == 1 && diaIngresso == 1)) {
//             recredenciado = "PPJ";
//         } else if (diffNascimento > 60 || (diffNascimento == 60 && mesIngresso <= 1 && diaIngresso == 1)) {
//             recredenciado = "PPS";
//         } else if (pontos >= regra.getPontosMinimos() && quantidade >= quantidadePeriodicosNecessarios) {
//             recredenciado = "Sim";
//         }

//         arquivo << docente.get_nome() << ";" << fixed << setprecision(1) << pontos << ";"
//                 << recredenciado << "\n";
//     }
// }

// void Reports::writePublicacoes(const string& diretorio, PPGI& ufes) {
//     ofstream arquivo(diretorio + PUBLICACOES);

//     if (!arquivo.is_open()) {
//         throw runtime_error("Erro ao abrir o arquivo " + diretorio + PUBLICACOES);
//     }

//     arquivo << "Ano;Sigla Veículo;Veículo;Qualis;Fator de Impacto;Título;Docentes\n";

//     auto publicacoes = ufes.get_publicacoes();

//     // Ordenar publicações
//     sort(publicacoes.begin(), publicacoes.end(), [](Publicacao & a, Publicacao & b) {
//         if (a.get_veiculo()->getQualis()->getValor() != b.get_veiculo()->getQualis()->getValor()) {
//             return a.get_veiculo()->getQualis()->getValor() < b.get_veiculo()->getQualis()->getValor();
//         }
//         if (a.get_ano() != b.get_ano()) {
//             return a.get_ano() > b.get_ano();
//         }
//         if (a.get_veiculo()->getSigla() != b.get_veiculo()->getSigla()) {
//             return a.get_veiculo()->getSigla() < b.get_veiculo()->getSigla();
//         }
//         return a.get_titulo() < b.get_titulo();
//     });

//     for (Publicacao & publicacao : publicacoes) {
//         string autores;
//         for (auto & autor : publicacao.get_autores()) {
//             autores += autor->get_nome() + ",";
//         }
//         if (!autores.empty()) {
//             autores.pop_back(); // Remover última vírgula
//         }

//         arquivo << publicacao.get_ano() << ";"
//                 << publicacao.get_veiculo()->getSigla() << ";"
//                 << publicacao.get_veiculo()->getNome() << ";"
//                 << publicacao->get_veiculo()->getQualis()->getValor() << ";"
//                 << fixed << setprecision(3) << publicacao.get_veiculo()->getImpacto() << ";"
//                 << publicacao.get_titulo() << ";"
//                 << autores << "\n";
//     }
// }

// void Reports::writeEstatisticas(const string& diretorio,PPGI& ufes) {
//     ofstream arquivo(diretorio + ESTATISTICAS);

//     if (!arquivo.is_open()) {
//         throw runtime_error("Erro ao abrir o arquivo " + diretorio + ESTATISTICAS);
//     }

//     arquivo << "Qualis;Qtd. Artigos;Média Artigos / Docente\n";

//     unordered_map<string, int> qualisArtigos;
//     unordered_map<string, double> qualisMediaDocentes;

//     for (Publicacao & publicacao : ufes.get_publicacoes()) {
//         string qualis = publicacao.get_veiculo()->getQualis()->getValor();
//         qualisArtigos[qualis]++;
//         qualisMediaDocentes[qualis] += 1.0 / publicacao.get_autores().size();
//     }

//     for (const auto& qualis : Qualis::VALORES) {
//         int artigos = qualisArtigos.count(qualis) ? qualisArtigos[qualis] : 0;
//         double media = qualisMediaDocentes.count(qualis) ? qualisMediaDocentes[qualis] : 0.0;
//         arquivo << qualis << ";" << artigos << ";" << fixed << setprecision(2) << media << "\n";
//     }
// }