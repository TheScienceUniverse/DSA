#include "../inc/graph.h"

Graph* create_graph () {
	Graph* graph = (Graph*) malloc (sizeof (Graph));
	
	if (graph != NULL) {
		graph -> any_vertex = NULL;
		graph -> vertex_list = create_list (0);
		graph -> edge_list = create_list (0);
	}

	return graph;
}

void delete_graph (Graph** graph_address) {
	if (*graph_address == NULL) {
		return;
	}

	Graph* graph = *graph_address;
	Vertex* vertex;
	Edge* edge;
	size_t i;
	
	// removing dependencies...
	for (i = 0; i < graph -> vertex_list -> item_count; i++) {
		vertex = *(graph -> vertex_list -> item_addresses + i);
		forget_list (&(vertex -> address_list));
	}

	for (i = 0; i < graph -> edge_list -> item_count; i++) {
		edge = *(graph -> edge_list -> item_addresses + i);
		edge -> vertex1 = NULL;
		edge -> vertex2 = NULL;
	}

	// deleting edges and vertices...
	if (graph -> edge_list != NULL) {
		delete_list (&(graph -> edge_list));
	}

	if (graph -> vertex_list != NULL) {
		delete_list (&(graph -> vertex_list));
	}

	graph = NULL;
	ERASE (graph_address, sizeof (Graph));
}

Route* create_route_data (char symbol, Vertex* next_vertex) {
	Route* route = malloc (sizeof (Route));

	if (route != NULL) {
		route -> data = create_data (DT_String, 1, &symbol);
		route -> next_vertex = next_vertex;
	}

	return route;
}

void add_vertex_to_graph (Graph* graph, Vertex* vertex) {
	if (graph == NULL) {
		perror ("Graph does not exist to add vertex!");
		return;
	}

	if (vertex == NULL) {
		perror ("Vertex does not exist to add in graph!");
		return;
	}

	if (vertex -> type != N_Graph) {
		perror ("Node is not graph type to add in graph!");
		return;
	}

	Vertex* new_vertex = duplicate_node (vertex);
	new_vertex -> name = append_integer_to_raw_string ("Vertex_", graph -> vertex_list -> item_count + 1);
	add_to_list (graph -> vertex_list, new_vertex, false);
	new_vertex = NULL;

	if (graph -> any_vertex == NULL) {
		graph -> any_vertex = vertex;
	}
}

Edge* create_edge_for_graph (Graph* graph, Vertex* vertex1, Vertex* vertex2, Data* weight) {
	if (vertex1 == NULL || vertex2 == NULL || weight == NULL) {
		perror ("Null data provided to create edge, that can't be done");
		return NULL;
	}

	Edge* edge = (Edge*) malloc (sizeof (Edge));

	if (edge != NULL) {
		edge -> name = append_integer_to_raw_string ("Edge_", graph -> edge_list -> item_count + 1);
		edge -> vertex1 = vertex1;
		edge -> vertex2 = vertex2;
		edge -> weight = duplicate_data (weight);
	}

	return edge;
}

void add_edge_to_graph (Graph* graph, Vertex* vertex1, Vertex* vertex2, Data* weight) {
	if (graph == NULL) {
		perror ("Graph does not exist to add edge!");
		return;
	}

	if (vertex1 == NULL || vertex2 == NULL || weight == NULL) {
		perror ("Null data provided to create edge, that can't be done!");
		return;
	}

	Edge* edge = create_edge_for_graph (graph, vertex1, vertex2, weight);

	if (edge == NULL) {
		perror ("Edge could not be created!");
		return;
	}

	// adding edge
	add_to_list (graph -> edge_list, edge, false);

	// adding vertex routing
	add_to_list (vertex1 -> address_list, vertex2, false);

	if (edge -> type != ET_Uniodirectional) {
		add_to_list (vertex2 -> address_list, vertex1, false);
	}
}

void display_edge (Edge* edge) {
	if (edge == NULL) {
		perror ("Edge does not exist to display!");
		return;
	}

	printf ("\n\t(");
	display_string (edge -> name);
	printf (") : ");
	display_node (edge -> vertex1);
	printf ("--[");
	display_data (edge -> weight);
	printf ("]--");
	display_node (edge -> vertex2);
}

void display_edge_list (List* edge_list) {
	if (edge_list == NULL) {
		perror ("Edge List does not exist to display!");
		return;
	}

	if (edge_list -> item_count == 0 || edge_list -> item_addresses == NULL) {
		perror ("Edge List is empty to display!");
		return;
	}

	for (size_t i = 0; i < edge_list -> item_count; i++) {
		display_edge (*(edge_list -> item_addresses + i));
	}
}

void display_graph (Graph* graph) {
	if (graph == NULL) {
		perror ("Graph does not exist to display!");
		return;
	}

	export_graph_data_for_web_view (graph);
	printf ("Graph data exported to JSON file to open in a webpage instead\n");
}

void display_graph_details (Graph* graph) {
	if (graph == NULL) {
		perror ("Graph does not exist to display!");
		return;
	}

	if (graph -> vertex_list == NULL) {
		perror ("Graph's vertex list does not exist to display!");
		return;
	}

	printf ("List of Vertices (%lu) : [", graph -> vertex_list -> item_count);

	for  (size_t i = 0; i < graph -> vertex_list -> item_count; i++) {
		printf ("\n\t");
		display_node (*(graph -> vertex_list -> item_addresses + i));
	}

	printf ("\n]\n");

	printf ("List of Edges (%lu) : [", graph -> edge_list -> item_count);
	display_edge_list (graph -> edge_list);
	printf ("\n]\n");
}

void export_graph_data_for_web_view (Graph* graph) {
	if (graph == NULL) {
		perror ("Graph does not exist to export!");
		return;
	}

	FILE* fpo = fopen ("../web/graph/data.js", "wb+");
	size_t i;
	Vertex* vertex;
	Edge* edge;

	fprintf (fpo, "const vertex_list = [");

	for (i = 0; i < graph -> vertex_list -> item_count; i++) {
		if (i > 0) {
			fprintf (fpo, ", ");
		}

		vertex = *(graph -> vertex_list -> item_addresses + i);
		fprintf (fpo, "\"%s\"", vertex -> name -> address);
	}

	fprintf (fpo, "];\n\nconst edge_list = [\n");

	for (i = 0; i < graph -> edge_list -> item_count; i++) {
		fprintf (fpo, "\t");

		if (i > 0) {
			fprintf (fpo, ", ");
		}

		edge = *(graph -> edge_list -> item_addresses + i);
		fprintf (fpo, "[\"%s\", \"%s\", \"%s\", \"W%lu\"]\n", edge -> name -> address, edge -> vertex1 -> name -> address, edge -> vertex2 -> name -> address, i);
	}

	fprintf (fpo, "];");

	fclose (fpo);
}

Vertex* get_vertex_by_id_from_graph (Graph* graph, size_t id) {
	if (graph == NULL) {
		perror ("Graph does not exist to get vertex from!");
		return NULL;
	}

	if (id > graph -> vertex_list -> item_count) {
		perror ("Graph does not have this vertex!");
		return NULL;
	}

	return *(graph -> vertex_list -> item_addresses + id - 1);
}