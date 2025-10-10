#include <iostream>
#include <vector>
#include <stdexcept>
#include <queue>
#include <algorithm>
#include <hw.h>


bool CalcGraph::topological_sort()
{
    int n = (int)vertices.size();
    std::vector<int> indeg(n, 0);
    for (const auto& e : edges)
    {
        indeg[e.inp_vertex_id]++;
    }
    std::queue<int> q;
    for (int i = 0; i < n; ++i)
        if (indeg[i] == 0)
            q.push(i);
    topo_order.clear();
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        topo_order.push_back(v);
        for (const auto& e : edges)
        {
            if (e.out_vertex_id == v)
            {
                indeg[e.inp_vertex_id]--;
                if (indeg[e.inp_vertex_id] == 0)
                    q.push(e.inp_vertex_id);
            }
        }
    }
    return topo_order.size() == vertices.size();
}

void CalcGraph::calculate_graph_inputs()
{
    int total_inputs = 0;
    int n = (int)vertices.size();
    std::vector<std::vector<bool>> connected_inputs(n);
    for (int i = 0; i < n; ++i)
        connected_inputs[i].resize(vertices[i]->num_inputs(), false);
    for (const auto& e : edges)
        connected_inputs[e.inp_vertex_id][e.inp_port_id] = true;
    graph_inputs.clear();
    for (int v = 0; v < n; ++v)
    {
        int inputs_num = vertices[v]->num_inputs();
        for (int inp_id = 0; inp_id < inputs_num; ++inp_id)
        {
            if (!connected_inputs[v][inp_id])
            {
                total_inputs++;
                graph_inputs.push_back(0.0);
            }
        }
    }
}

void CalcGraph::build_global_input_map()
{
    global_input_map.clear();
    int n = (int)vertices.size();
    std::vector<std::vector<bool>> connected_inputs(n);
    for (int i = 0; i < n; ++i)
        connected_inputs[i].resize(vertices[i]->num_inputs(), false);
    for (const auto& e : edges)
        connected_inputs[e.inp_vertex_id][e.inp_port_id] = true;
    for (int v = 0; v < n; ++v)
    {
        int inputs_num = vertices[v]->num_inputs();
        for (int inp_id = 0; inp_id < inputs_num; ++inp_id)
        {
            if (!connected_inputs[v][inp_id])
            {
                global_input_map.emplace_back(v, inp_id);
            }
        }
    }
}
void CalcGraph::calculate_graph_outputs()
{
    int n = (int)vertices.size();
    std::vector<std::vector<bool>> connected_outputs(n);
    for (int i = 0; i < n; ++i)
        connected_outputs[i].resize(vertices[i]->num_outputs(), false);
    for (const auto& e : edges)
        connected_outputs[e.out_vertex_id][e.out_port_id] = true;
    graph_outputs.clear();
    for (int v = 0; v < n; ++v)
    {
        int outputs_num = vertices[v]->num_outputs();
        for (int out_id = 0; out_id < outputs_num; ++out_id)
        {
            if (!connected_outputs[v][out_id])
            {
                graph_outputs.push_back(0.0);
            }
        }
    }
}

void CalcGraph::build_global_output_map()
{
    global_output_map.clear();
    int n = (int)vertices.size();
    std::vector<std::vector<bool>> connected_outputs(n);
    for (int i = 0; i < n; ++i)
        connected_outputs[i].resize(vertices[i]->num_outputs(), false);
    for (const auto& e : edges)
        connected_outputs[e.out_vertex_id][e.out_port_id] = true;
    for (int v = 0; v < n; ++v)
    {
        int outputs_num = vertices[v]->num_outputs();
        for (int out_id = 0; out_id < outputs_num; ++out_id)
        {
            if (!connected_outputs[v][out_id])
            {
                global_output_map.emplace_back(v, out_id);
            }
        }
    }
}

void CalcGraph::set_data(const std::vector<Vertex*>& verts, const std::vector<Edge>& edgs)
{
    vertices = verts;
    edges = edgs;
    if (!topological_sort())
    {
        throw std::runtime_error("Graph contains cycles");
    }
    calculate_graph_inputs();
    build_global_input_map();
    calculate_graph_outputs();
    build_global_output_map();
}

int CalcGraph::num_inputs() const
{
    return (int)graph_inputs.size();
}

void CalcGraph::set_input(int inp_idx, double inp_val)
{
    if (inp_idx < 0 || inp_idx >= (int)graph_inputs.size())
        throw std::out_of_range("Input index out of range");
    graph_inputs[inp_idx] = inp_val;
}

int CalcGraph::num_outputs() const
{
    return (int)graph_outputs.size();
}

double CalcGraph::get_output(int out_idx)
{
    if (out_idx < 0 || out_idx >= (int)graph_outputs.size())
        throw std::out_of_range("Output index out of range");
    return graph_outputs[out_idx];
}

void CalcGraph::calc_value()
{
    for (size_t i = 0; i < graph_inputs.size(); ++i)
    {
        int v = global_input_map[i].first;
        int port = global_input_map[i].second;
        vertices[v]->set_input(port, graph_inputs[i]);
    }
    for (int vert : topo_order)
    {
        vertices[vert]->calc_value();
        for (const auto& e : edges)
        {
            if (e.out_vertex_id == vert)
            {
                double val = vertices[vert]->get_output(e.out_port_id);
                vertices[e.inp_vertex_id]->set_input(e.inp_port_id, val);
            }
        }
    }
    for (size_t i = 0; i < graph_outputs.size(); ++i)
    {
        int v = global_output_map[i].first;
        int port = global_output_map[i].second;
        graph_outputs[i] = vertices[v]->get_output(port);
    }
}


int PlusOperator::num_inputs() const
{
    return 2;
}
void PlusOperator::set_input(int inp_idx, double inp_val)
{
    if (inp_idx < 0 || inp_idx >= 2)
        throw std::out_of_range("Bad inp_idx in PlusOperator::set_input");
    input_value[inp_idx] = inp_val;
}
void PlusOperator::calc_value()
{
    output_value = input_value[0] + input_value[1];
}
int PlusOperator::num_outputs() const
{
    return 1;
}
double PlusOperator::get_output(int out_idx)
{
    if (out_idx != 0)
        throw std::out_of_range("Bad out_idx in PlusOperator::get_output");
    return output_value;
}

int MulOperator::num_inputs() const
{
    return 2;
}
void MulOperator::set_input(int inp_idx, double inp_val)
{
    if (inp_idx < 0 || inp_idx >= 2)
        throw std::out_of_range("inp_idx in MulOperator::set_input out of range");
    input_value[inp_idx] = inp_val;
}
void MulOperator::calc_value()
{
    output_value = input_value[0] * input_value[1];
}
int MulOperator::num_outputs() const
{
    return 1;
}
double MulOperator::get_output(int out_idx)
{
    if (out_idx != 0)
        throw std::out_of_range("out_idx in MulOperator::get_output out of range");
    return output_value;
}

int MinusOperator::num_inputs() const
{
    return 2;
}
void MinusOperator::set_input(int inp_idx, double inp_val)
{
    if (inp_idx < 0 || inp_idx >= 2)
        throw std::out_of_range("Bad inp_idx in MinusOperator::set_input");
    input_value[inp_idx] = inp_val;
}
void MinusOperator::calc_value()
{
    output_value = input_value[0] - input_value[1];
}
int MinusOperator::num_outputs() const
{
    return 1;
}
double MinusOperator::get_output(int out_idx)
{
    if (out_idx != 0)
        throw std::out_of_range("Bad out_idx in MinusOperator::get_output");
    return output_value;
}

int main() {
    CalcGraph cg;

    std::vector<Vertex*> vertex;
    std::vector<Edge> edges;

    vertex.push_back(new PlusOperator()); 
    vertex.push_back(new PlusOperator()); 

    edges.push_back(Edge{ 0, 0, 1, 0 });

    cg.set_data(vertex, edges);

    std::cout << "Number of graph inputs: " << cg.num_inputs() << std::endl;
    std::cout << "Number of graph outputs: " << cg.num_outputs() << std::endl; 
    cg.set_input(0, 1.0);
    cg.set_input(1, 2.0);
    cg.set_input(2, 3.0);

    cg.calc_value();

    std::cout << "Graph output: " << cg.get_output(0) << std::endl; 

    return 0;
}
