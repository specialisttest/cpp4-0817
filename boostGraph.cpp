#include <iostream>
#include <vector>
#include <string>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>


// ���������� ��� �����
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                       boost::property<boost::vertex_name_t, std::string>,
                       boost::property<boost::edge_weight_t, int>> Graph;
                       
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIterator;

int main() {
	system("chcp 1251 > nul");
	
	// ������ ����
	Graph g;
	
	
	// ��������� ������� � ���������� ������
    Vertex v0 = add_vertex(std::string("������"), g);
    Vertex v1 = add_vertex(std::string("���"), g);
    Vertex v2 = add_vertex(std::string("������"), g);
    Vertex v3 = add_vertex(std::string("�����������"), g);	
	
    // ��������� ����� � ������
    add_edge(v0, v1, 710, g);  // ������ -> ���
    add_edge(v0, v2, 830, g);  // ������ -> ������
    add_edge(v1, v3, 3990, g); // ��� -> �����������
    add_edge(v2, v3, 2500, g); // ������ -> �����������
    add_edge(v3, v0, 3300, g); // ����������� -> ������	
    
    std::cout << "=== ��������� ������ (�����) ===" << std::endl;
    
    // 1. �������� �� ���� ��������
    std::cout << "\n1. ��� ������� �����:" << std::endl;
    std::pair<VertexIterator, VertexIterator> vp = vertices(g);
    for (VertexIterator vi = vp.first; vi != vp.second; ++vi) {
        std::cout << "������� " << *vi << ": " 
                  << get(boost::vertex_name, g, *vi) << std::endl;
    }
    
    std::cout << "\n=== ��������� ����� (���) ===" << std::endl;
	
	// 2. �������� �� ���� ������
    std::cout << "\n2. ��� ����� �����:" << std::endl;
    std::pair<EdgeIterator, EdgeIterator> ep = edges(g);
    for (EdgeIterator ei = ep.first; ei != ep.second; ++ei) {
        Vertex source_v = source(*ei, g);
        Vertex target_v = target(*ei, g);
        std::cout << "����� " << *ei << ": " 
                  << get(boost::vertex_name, g, source_v) << " -> " 
                  << get(boost::vertex_name, g, target_v) 
                  << " (����������: " << get(boost::edge_weight, g, *ei) << " ��)" 
                  << std::endl;
    }
	
	
	    // ����� �������� ���������� � �����
    std::cout << "\n=== ���������� � ����� ===" << std::endl;
    std::cout << "���������� ������: " << num_vertices(g) << std::endl;
    std::cout << "���������� �����: " << num_edges(g) << std::endl;
    
	return 0;
}
