#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "helper/dslib_error.h"
#include "dslib_list.h"
#include "dslib_graph.h"

#define FREE(ptr) do { free((ptr)); (ptr) = NULL; } while(0)

struct Graph {
	List vertex;
	size_t elemSize;
	int isCostly;
};

typedef struct Vertex {
	List adj;
	void* info;
} Vertex;

struct Edge {
	Vertex* pVertex;
	size_t cost;
};

Graph dslib_graph_init(size_t size, userFunction free, int isCostly)
{
	dslib_error = DSLIB_SUCCESS;

	Graph graph = malloc(sizeof(*graph));
	if (!graph) {
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return NULL;
	}

	graph->vertex = dslib_list_init(sizeof(Vertex), free);
	if (!graph->vertex) {
		FREE(graph);
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return NULL;
	}

	graph->elemSize = size;
	graph->isCostly = isCostly;
	return graph;
}

void dslib_graph_graph_clear(Graph const graph)
{
	assert(graph != NULL);

	dslib_error = DSLIB_SUCCESS;

	ListIterator it;
	dslib_list_foreach(it, graph->vertex) {
		GraphIterator vertex = dslib_list_iterator_dereference(it);
		dslib_list_clear(dslib_graph_vertex_getAdjacents(vertex));
	}
	dslib_list_clear(graph->vertex);
	free(graph);
}

int dslib_graph_empty(const Graph const graph)
{
	assert(graph != NULL);

	dslib_error = DSLIB_SUCCESS;

	return dslib_list_empty(graph->vertex);
}

List dslib_graph_vertexList(const Graph const graph)
{
	assert(graph != NULL);
	return graph->vertex;
}

GraphIterator dslib_graph_vertex_add(const Graph const graph, void* val)
{
	assert(graph != NULL);

	dslib_error = DSLIB_SUCCESS;

	Vertex vertex;

	vertex.info = malloc(graph->elemSize);
	if (!vertex.info) {
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return NULL;
	}

	vertex.adj = dslib_list_init(sizeof(struct Edge), NULL);
	if (!vertex.adj) {
		FREE(vertex.info);
		dslib_error = DSLIB_FAILED_TO_ALLOCATE_MEMORY;
		return NULL;
	}

	memcpy(vertex.info, val, graph->elemSize);
	dslib_list_push_back(graph->vertex, &vertex);

	return (GraphIterator)dslib_list_iterator_dereference(dslib_list_iterator_rbegin(graph->vertex));
}

void dslib_graph_vertex_remove(const Graph const graph, GraphIterator const vertex)
{
	assert(graph != NULL);
	assert(vertex != NULL);

	dslib_error = DSLIB_SUCCESS;

	/* saved stores the ListNode where the vertex is at so that it can be
	 * removed later
	 */
	ListIterator saved, it;
	dslib_list_foreach(it, graph->vertex) {
		GraphIterator temp = dslib_list_iterator_dereference(it);
		if (temp == vertex) {
			saved = it;
			continue;
		}
		ListIterator it2;
		dslib_list_foreach(it2, temp->adj) {
			Edge edge = dslib_list_iterator_dereference(it2);
			if (edge->pVertex == vertex) {
				dslib_list_erase(temp->adj, it2);
			}
		}
	}
	dslib_list_clear(((GraphIterator)dslib_list_iterator_dereference(saved))->adj);
	dslib_list_erase(graph->vertex, saved);
}

void* dslib_graph_vertex_getInfo(const GraphIterator const vertex)
{
	assert(vertex != NULL);
	return vertex->info;
}

List dslib_graph_vertex_getAdjacents(const GraphIterator const vertex)
{
	assert(vertex != NULL);
	return vertex->adj;
}

size_t dslib_graph_vertex_inDegree(const Graph const graph, const GraphIterator const vertex)
{
	assert(graph != NULL);
	assert(vertex != NULL);

	dslib_error = DSLIB_SUCCESS;

	size_t degree = 0;

	ListIterator it;
	dslib_list_foreach(it, graph->vertex) {
		GraphIterator temp = dslib_list_iterator_dereference(it);
		ListIterator it2;
		dslib_list_foreach(it2, temp->adj) {
			Edge edge = dslib_list_iterator_dereference(it2);
			if (edge->pVertex == vertex) {
				degree++;
			}
		}
	}
	return degree;
}

size_t dslib_graph_vertex_outDegree(const Graph const graph, const GraphIterator const vertex)
{
	assert(graph != NULL);
	assert(vertex != NULL);
	return dslib_list_size(dslib_graph_vertex_getAdjacents(vertex));
}

size_t dslib_graph_vertex_count(const Graph const graph)
{
	assert(graph != NULL);
	return dslib_list_size(graph->vertex);
}

int dslib_graph_edge_exists(const Graph const graph, const GraphIterator const a, const GraphIterator const b)
{
	assert(graph != NULL);
	assert(a != NULL);
	assert(b != NULL);

	dslib_error = DSLIB_SUCCESS;

	ListIterator it;
	dslib_list_foreach(it, a->adj) {
		Edge edge = dslib_list_iterator_dereference(it);
		if (edge->pVertex == b) {
			return 1;
		}
	}
	return 0;
}

void dslib_graph_edge_add_directed(const Graph const graph, const GraphIterator const a, const GraphIterator const b, size_t cost)
{
	assert(graph != NULL);
	assert(a != NULL);
	assert(b != NULL);

	dslib_error = DSLIB_SUCCESS;

	struct Edge edge;
	edge.pVertex = b;
	edge.cost = cost;
	dslib_list_push_back(a->adj, &edge);
}

void dslib_graph_edge_add_undirected(const Graph const graph, const GraphIterator const a, const GraphIterator const b, size_t cost)
{
	assert(graph != NULL);
	assert(a != NULL);
	assert(b != NULL);

	dslib_error = DSLIB_SUCCESS;

	dslib_graph_edge_add_directed(graph, a, b, cost);
	dslib_graph_edge_add_directed(graph, b, a, cost);
}

void dslib_graph_edge_remove_directed(const Graph const graph, const GraphIterator const a, const GraphIterator const b)
{
	assert(graph != NULL);
	assert(a != NULL);
	assert(b != NULL);

	dslib_error = DSLIB_SUCCESS;

	if (!dslib_graph_edge_exists(graph, a, b)) {
		dslib_error = DSLIB_ELEMENT_NOT_FOUND;
		return;
	}

	ListIterator it;
	dslib_list_foreach(it, a->adj) {
		Edge edge = dslib_list_iterator_dereference(it);
		if (edge->pVertex == b) {
			dslib_list_erase(a->adj, it);
			break;
		}
	}
}

void dslib_graph_edge_remove_undirected(const Graph const graph, const GraphIterator const a, const GraphIterator const b)
{
	assert(graph != NULL);
	assert(a != NULL);
	assert(b != NULL);

	dslib_error = DSLIB_SUCCESS;

	dslib_graph_edge_remove_directed(graph, a, b);
	dslib_graph_edge_remove_directed(graph, b, a);
}

size_t dslib_graph_edge_count_directed(const Graph const graph)
{
	assert(graph != NULL);

	size_t edgeCount = 0;

	ListIterator it;
	dslib_list_foreach(it, graph->vertex) {
		GraphIterator vertex = dslib_list_iterator_dereference(it);
		edgeCount += dslib_list_size(vertex->adj);
	}

	return edgeCount;
}

size_t dslib_graph_edge_count_undirected(const Graph const graph)
{
	assert(graph != NULL);
	return dslib_graph_edge_count_directed(graph) / 2;
}

size_t graph_edge_get_cost(const Edge const edge)
{
	assert(edge != NULL);
	return edge->cost;
}

void graph_edge_set_cost(Edge const edge, size_t cost)
{
	assert(edge != NULL);
	edge->cost = cost;
}

GraphIterator dslib_graph_edge_pointsTo(const Edge const edge)
{
	assert(edge != NULL);
	return edge->pVertex;
}

GraphIterator dslib_graph_iterator_begin(Graph graph)
{
	assert(graph != NULL);
	return (GraphIterator)dslib_list_iterator_dereference(dslib_list_iterator_begin(graph->vertex));
}

/* to add: a way to actually iterate graphs */
