#include <vector>


class Vertex
{
public:
    virtual ~Vertex() {}
    virtual int num_inputs() const = 0;
    virtual void set_input(int inp_idx, double inp_val) = 0;
    virtual int num_outputs() const = 0;
    virtual double get_output(int out_idx) = 0;
    virtual void calc_value() = 0;
};

struct Edge
{
    int out_vertex_id;
    int out_port_id;
    int inp_vertex_id;
    int inp_port_id;
};

class CalcGraph : public Vertex
{
private:
    std::vector<Vertex*> vertices;
    std::vector<Edge> edges;
    
    std::vector<int> topo_order;
    std::vector<int> input_counts;
    std::vector<double> graph_inputs;
    std::vector<double> graph_outputs;
    std::vector<std::pair<int, int>> global_output_map;
    std::vector<std::pair<int, int>> global_input_map;

    bool topological_sort();
    void calculate_graph_inputs();
    void calculate_graph_outputs();
    void build_global_input_map();
    void build_global_output_map();
public:
    void set_data(const std::vector<Vertex*>& verts, const std::vector<Edge>& edgs);
    int num_inputs() const override;
    void set_input(int inp_idx, double inp_val) override;
    int num_outputs() const override;
    double get_output(int out_idx) override;
    void calc_value() override;

    ~CalcGraph()
    {
        for (Vertex* v : vertices) {
            delete v;
        }
    }
};

class PlusOperator : public Vertex
{
    double input_value[2] = { 0 };
    double output_value = 0.0;
public:
    int num_inputs() const override;
    void set_input(int inp_idx, double inp_val) override;
    void calc_value() override;
    int num_outputs() const override ;
    double get_output(int out_idx) override;
};


class MulOperator: public Vertex
{
private:
    double input_value[2] = { 0 };
    double output_value = 0.0;

public:
    int num_inputs() const override;
    void set_input(int inp_idx, double inp_val) override;
    void calc_value() override;
    int num_outputs() const override;
    double get_output(int out_idx) override;
};

class MinusOperator: public Vertex
{
    double input_value[2] = { 0 };
    double output_value = 0.0;
public:
    int num_inputs() const override;
    void set_input(int inp_idx, double inp_val) override;
    void calc_value() override;
    int num_outputs() const override; 
    double get_output(int out_idx) override;
};

