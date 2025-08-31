#include <iostream>
#include <vector>
#include <string>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>


// Определяем тип графа
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                       boost::property<boost::vertex_name_t, std::string>,
                       boost::property<boost::edge_weight_t, int>> Graph;
                       
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIterator;

int main() {
	system("chcp 1251 > nul");
	
	// Создаём граф
	Graph g;
	
	
	// Добавляем вершины с названиями города
    Vertex v0 = add_vertex(std::string("Москва"), g);
    Vertex v1 = add_vertex(std::string("СПб"), g);
    Vertex v2 = add_vertex(std::string("Казань"), g);
    Vertex v3 = add_vertex(std::string("Новосибирск"), g);	
	
    // Добавляем ребра с весами
    add_edge(v0, v1, 710, g);  // Москва -> СПб
    add_edge(v0, v2, 830, g);  // Москва -> Казань
    add_edge(v1, v3, 3990, g); // СПб -> Новосибирск
    add_edge(v2, v3, 2500, g); // Казань -> Новосибирск
    add_edge(v3, v0, 3300, g); // Новосибирск -> Москва	
    
    std::cout << "=== ИТЕРАТОРЫ ВЕРШИН (УЗЛОВ) ===" << std::endl;
    
    // 1. Итератор по всем вершинам
    std::cout << "\n1. Все вершины графа:" << std::endl;
    std::pair<VertexIterator, VertexIterator> vp = vertices(g);
    for (VertexIterator vi = vp.first; vi != vp.second; ++vi) {
        std::cout << "Вершина " << *vi << ": " 
                  << get(boost::vertex_name, g, *vi) << std::endl;
    }
    
    std::cout << "\n=== ИТЕРАТОРЫ РЕБЕР (ДУГ) ===" << std::endl;
	
	// 2. Итератор по всем ребрам
    std::cout << "\n2. Все ребра графа:" << std::endl;
    std::pair<EdgeIterator, EdgeIterator> ep = edges(g);
    for (EdgeIterator ei = ep.first; ei != ep.second; ++ei) {
        Vertex source_v = source(*ei, g);
        Vertex target_v = target(*ei, g);
        std::cout << "Ребро " << *ei << ": " 
                  << get(boost::vertex_name, g, source_v) << " -> " 
                  << get(boost::vertex_name, g, target_v) 
                  << " (расстояние: " << get(boost::edge_weight, g, *ei) << " км)" 
                  << std::endl;
    }
	
	
	    // Вывод основной информации о графе
    std::cout << "\n=== ИНФОРМАЦИЯ О ГРАФЕ ===" << std::endl;
    std::cout << "Количество вершин: " << num_vertices(g) << std::endl;
    std::cout << "Количество ребер: " << num_edges(g) << std::endl;
    
	return 0;
}
