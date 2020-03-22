
# we want to order the structs appropriately
order_struct_by_dependency <- function(struct_info) {
    # first we define all vertices
    all_types_used <- sort(c("_root", unique(c(struct_info$type, struct_info$category_name))))
    vertices <- data.frame(name=all_types_used, stringsAsFactors=FALSE)
    # now a data frame with all the edges
    # also note that each node should be connected to the root
    root_edges <- data.frame(from="_root", to=all_types_used, stringsAsFactors=FALSE)
    other_edges <- data.frame(from=struct_info$type, to=struct_info$category_name, stringsAsFactors=FALSE)
    all_edges <- rbind(root_edges, other_edges)

    g <- igraph::graph_from_data_frame(all_edges, directed=TRUE, vertices=vertices)
    # reorder
    g_topo_order <- igraph::topo_sort(g, mode="out")
    priority_df <- data.frame(category_name=names(g_topo_order), stringsAsFactors=FALSE)
    priority_df$priority <- seq_along(priority_df$category_name)
    struct_info <- dplyr::left_join(struct_info, priority_df) 
    struct_info <- dplyr::arrange(struct_info, priority)
    return(struct_info)  
}
