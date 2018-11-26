public class Node {
	
	int n;		//키의 개수
	int m;		//자식노드 개수 최대
	int[] k;	//키 배열
	Node[] p;	//자식노드 배열
	
	//생성자
	public Node(int m) {
		n = 0;
		this.m = m;
		k = new int[m];
		p = new Node[m];
		for(int i = 0; i < m; i++) {
			k[i] = 0;
			p[i] = null;
		}
	}
	
	//복사 메소드
	public void copyNode(Node origin) {
		n = origin.n;
		for(int i = 0; i <= n; i++) {
			k[i] = origin.k[i];
			p[i] = origin.p[i];
		}
	}
	
	//getNode 메소드
	public void getNode(int key) {
		n = 1;
		for(int i = 0; i < m; i++) {
			k[i] = 0;
			p[i] = null;
		}
		k[1] = key;		
	}
}
