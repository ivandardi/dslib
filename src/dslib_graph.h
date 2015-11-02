#ifndef DSLIB_GRAPH_H_INCLUDED
#define DSLIB_GRAPH_H_INCLUDED

/**
 * \file
 *
 * \brief A graph.
 *
 * A graph is a complex structure, composed of vertices and edges in its most
 * crude description. In dslib, it's implemented as a list of vertices that have
 * their info plus a list of edges that have a cost and a pointer to the vertex
 * that they're adjacent to. Because of that, the graph has the following time
 * complexity, where V is the number of vertices and E is the number of edges:
 *
 * * clear: O(V * E)
 *
 * * vertex_add: O(1)
 *
 * * vertex_remove: O(E)
 *
 * * vertex_inDegree: O(V * E)
 *
 * * vertex_outDegree: O(1)
 *
 * * vertex_count: O(1)
 *
 * * edge_exists: O(E)
 *
 * * edge_add_directed: O(1)
 *
 * * edge_add_undirected: O(1)
 *
 * * edge_remove_directed: O(E)
 *
 * * edge_remove_undirected: O(E)
 *
 * * edge_count_directed: O(V)
 *
 * * edge_count_undirected: O(V)
 *
 * The dslib graph provides iterators, but they're currently very limited.
 */

#include "helper/dslib_typedefs.h"

/**
 * \brief Initializes a graph.
 *
 * \param size Size of the elements of the list in bytes. Use sizeof(type) as
 *        the argument.
 * \param free Pointer to a function that takes a void* parameter and returns
 *        void. It's used in case the graph contains malloc'd pointers so that
 *        it doesn't leak memory. If the types used don't contain malloc'd
 *        pointers, this can be passed as NULL.
 * \param isCostly Determines whether or not the edges have costs to them. Used
 *        when iterating through the graph. 0 is false and everything else is
 *        true.
 * \return An initialized graph.
 *
 * \sa dslib_graph_
 */
Graph dslib_graph_init(size_t size, userFunction free, int isCostly);

/**
 * \brief Removes all elements from the graph (which are destroyed), and then
 *        destroys the graph itself.
 *
 * \param list The graph.
 *
 * \sa dslib_graph_init()
 */
void dslib_graph_graph_clear(Graph const graph);

/**
 * \brief Returns whether the graph is empty (whether its size is 0).
 *
 * \param graph The graph.
 * \return 1 if the number of vertices in the graph is 0, 0 otherwise.
 */
int dslib_graph_empty(const Graph const graph);

/**
 * \brief Returns a list containing all the vertices in a graph.
 *
 * \param graph The graph
 * \return A list of vertices in the graph.
 *
 * \sa dslib_graph_vertex_getAdjacents()
 */
List dslib_graph_vertexList(const Graph const graph);

/**
 * \brief Adds a vertex to the graph. The content of val is copied to the
 *        inserted element.
 *
 * \param graph The graph.
 * \param val Value to be copied to the inserted element.
 * \return A GraphIterator to the vertex that was added.
 *
 * \sa dslib_graph_vertex_remove()
 */
GraphIterator dslib_graph_vertex_add(const Graph const graph, void* val);

/**
 * \brief Removes a vertex from the graph. It also removes the edges related to
 *        the removed vertex.
 *
 * \param graph The graph.
 * \param vertex Iterator that points to the vertex to be removed.
 *
* \sa dslib_graph_vertex_add()
 */
void dslib_graph_vertex_remove(const Graph const graph, GraphIterator const vertex);

/**
 * \brief Returns the information stored in a vertex.
 *
 * \param vertex The vertex.
 * \return A void pointer to the stored information.
 */
void* dslib_graph_vertex_getInfo(const GraphIterator const vertex);

/**
 * \brief Returns a list of Edges, which contain pointers to the adjacent
 *        vertices, as well as the cost to them, if any.
 *
 * \param vertex The vertex.
 * \return A list of adjacent Edges.
 *
 * \sa dslib_graph_vertexList()
 */
List dslib_graph_vertex_getAdjacents(const GraphIterator const vertex);

/**
 * \brief Returns the in-degree of a vertex.
 *
 * \param graph The graph.
 * \param vertex The vertex.
 * \return The in-degree if the vertex.
 *
 * \sa dslib_graph_vertex_outDegree()
 */
size_t dslib_graph_vertex_inDegree(const Graph const graph, const GraphIterator const vertex);

/**
 * \brief Returns the out-degree of a vertex.
 *
 * \param graph The graph.
 * \param vertex The vertex.
 * \return The out-degree if the vertex.
 *
 * \sa dslib_graph_vertex_inDegree()
 */
size_t dslib_graph_vertex_outDegree(const Graph const graph, const GraphIterator const vertex);

/**
 * \brief Returns the number of vertices in a graph.
 *
 * \param graph The graph.
 * \return The number of vertices in the graph.
 *
 * \sa dslib_graph_edge_count_directed(), dslib_graph_edge_count_undirected()
 */
size_t dslib_graph_vertex_count(const Graph const graph);

/**
 * \brief Tells whether the edge (a,b) exists.
 *
 * \param graph The graph.
 * \param a A GraphIterator pointing to a vertex.
 * \param b A GraphIterator pointing to a vertex.
 * \return 1 if an edge exists, 0 otherwise.
 *
 * \sa dslib_graph_edge_add_directed(), dslib_graph_edge_add_undirected()
 */
int dslib_graph_edge_exists(const Graph const graph, const GraphIterator const a, const GraphIterator const b);

/**
 * \brief Adds a directed edge (a,b) between two vertices.
 *
 * \param graph The graph.
 * \param a A GraphIterator pointing to a vertex.
 * \param b A GraphIterator pointing to a vertex.
 * \param cost The cost of the edge. The value passed here doesn't matter if the
 *        graph isn't costly.
 *
 * \sa dslib_graph_edge_add_undirected()
 */
void dslib_graph_edge_add_directed(const Graph const graph, const GraphIterator const a, const GraphIterator const b, size_t cost);

/**
 * \brief Adds a undirected edge (a,b) between two vertices.
 *
 * It actually adds both (a,b) and (b,a) edges. If the number of edges of a
 * fully undirected graph is desired, use dslib_graph_edge_count_undirected().
 *
 * \param graph The graph.
 * \param a A GraphIterator pointing to a vertex.
 * \param b A GraphIterator pointing to a vertex.
 * \param cost The cost of the edge. The value passed here doesn't matter if the
 *        graph isn't costly.
 *
 * \sa dslib_graph_edge_add_directed()
 */
void dslib_graph_edge_add_undirected(const Graph const graph, const GraphIterator const a, const GraphIterator const b, size_t cost);

/**
 * \brief Removes a directed edge (a,b) between two vertices.
 *
 * \param graph The graph.
 * \param a A GraphIterator pointing to a vertex.
 * \param b A GraphIterator pointing to a vertex.
 *
 * \sa dslib_graph_edge_add_directed(), dslib_graph_edge_remove_undirected()
 */
void dslib_graph_edge_remove_directed(const Graph const graph, const GraphIterator const a, const GraphIterator const b);

/**
 * \brief Removes an undirected edge (a,b) between two vertices.
*
 * It actually removes both (a,b) and (b,a) edges. If the number of edges of a
 * fully undirected graph is desired, use dslib_graph_edge_count_undirected().
 *
 * \param graph The graph.
 * \param a A GraphIterator pointing to a vertex.
 * \param b A GraphIterator pointing to a vertex.
 *
 * \sa dslib_graph_edge_add_undirected(), dslib_graph_edge_remove_directed()
 */
void dslib_graph_edge_remove_undirected(const Graph const graph, const GraphIterator const a, const GraphIterator const b);

/**
 * \brief Returns the number of edges in a directed graph.
 *
 * \param graph The graph.
 * \return The number of edges in a directed graph.
 *
 * \sa dslib_graph_edge_count_undirected()
 */
size_t dslib_graph_edge_count_directed(const Graph const graph);

/**
 * \brief Returns the number of edges in an undirected graph.
 *
 * Since an undirected graph actually has two edges (a,b) and (b,a) to represent
 * a single edge, this function just returns the total number of edges divided
 * by 2.
 *
 * \param graph The graph.
 * \return the The number of edges in an undirected graph.
 *
 * \sa dslib_graph_edge_count_directed()
 */
size_t dslib_graph_edge_count_undirected(const Graph const graph);

/**
 * \brief Returns the cost of an edge.
 *
 * \param graph The edge.
 * \return The cost of the edge.
 *
 * \sa dslib_graph_edge_set_cost()
 */
size_t dslib_graph_edge_get_cost(const Edge const edge);

/**
 * \brief Sets the cost of an edge.
 *
 * \param graph The edge.
 *
 * \sa dslib_graph_edge_get_cost()
 */
void dslib_graph_edge_set_cost(Edge const edge, size_t cost);

/**
 * \brief Returns a GraphIterator to the vertex that the edge points to.
 *
 * \param edge The edge.
 * \return GraphIterator to the vertex that the edge points to.
 */
GraphIterator dslib_graph_edge_pointsTo(const Edge const edge);

GraphIterator dslib_graph_iterator_begin(Graph graph);

#endif /* DSLIB_GRAPH_H_INCLUDED */
