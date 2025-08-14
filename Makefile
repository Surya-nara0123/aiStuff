regenate_graph:
	@python3 create_graph.py

compile:
	@g++ bms.c++ -o output/bms
	@g++ dfs.c++ -o output/dfs
	@g++ bfs.c++ -o output/bfs
	@g++ dfs_bfs.c++ -o output/dfs_bfs
	@g++ dfs_history.c++ -o output/dfs_hitory
	@g++ bfs_history.c++ -o output/bfs_hitory
	@g++ hc.c++ -o output/hc
	@g++ hc_history.c++ -o output/hc_history

run_bms:
	@output/bms

run_dfs:
	@output/dfs

run_bfs:
	@output/bfs

run_dfs_bfs:
	@output/dfs_bfs

run_dfs_history:
	@output/dfs_hitory

run_bfs_history:
	@output/bfs_hitory

run_hc:
	@output/bfs

run_hc_history:
	@output/bfs
