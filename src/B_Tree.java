import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Stack;

public class B_Tree {
	
	public static void insertKey(Node node, int newKey, Node left, Node right) {
		
		int i = 1;
		while(i <= node.n && newKey > node.k[i]) 
			i++;
		
		if (node.n < i) {
			node.k[i] = newKey;
			//if(left != null)
				node.p[i-1] = left;
			//if(right != null)
				node.p[i] = right;
			node.n++;
		}
		else {
			int tempKey = node.k[i];
			node.k[i] = newKey;
			//if(left != null)
				node.p[i-1] = left;
			insertKey(node, tempKey, right, node.p[i]);
		}
	}
	
	public static void insertBT(Node root, int m, int newKey) {
		
		if(root.n == 0) {
			root.getNode(newKey);
			return;
		}
		
		Node x = root;
		Stack<Node> stack = new Stack<Node>();
		int i;

		do {
			i = 1;		//newKey가 삽입될 인덱스
			
			//탐색
			while(i <= x.n && newKey > x.k[i]) 
				i++;
			
			//이미 존재
			if(i <= x.n && newKey == x.k[i])
				return;
			
			//i는 newKey < x.k[i]를 만족하거나 i > n을 만족
			stack.add(x);
						
			x = x.p[i-1];
			
		}while(x != null);
		
		boolean finished = false; 
		x = stack.pop();
		
		Node left = null;
		Node right = null;
		do {
			
			//삽입 후 오버플로우가 아닐 경우 적절한 위치에 삽입
			if(x.n < m-1) {
				insertKey(x, newKey, left, right);
				finished = true;
			}else {
				
				Node tempNode = new Node(m+1);
				tempNode.copyNode(x);
				
				insertKey(tempNode, newKey, left, right);
				
				newKey = tempNode.k[m/2 + 1];
				//System.out.printf("newKey = %d\n", newKey);
				
				left = new Node(m);
				left.p[0] = tempNode.p[0];
				for(int j = 1; j <= m/2; j++) {
					left.k[j] = tempNode.k[j];
					left.p[j] = tempNode.p[j];
					left.n++;
				}
				
				//System.out.printf("left의 첫번째 = %d\n", left.k[1]);

				
				right = new Node(m);
				right.p[0] = tempNode.p[m/2 + 1];
				
				int j = m/2 + 2;
				int k = 1;
				
				do {
					right.k[k] = tempNode.k[j];
					right.p[k] = tempNode.p[j];
					right.n++;
					j++;
					k++;					
				}while(j != m + 1);	
				
				//System.out.printf("right의 첫번째 = %d\n", right.k[1]);

				if(!stack.empty()) {
					x = stack.pop();
				}else {
					root.getNode(newKey);
					root.p[0] = left;
					root.p[1] = right;
					//System.out.printf("left의 키 = %d, y의 키 = %d\n", left.k[1], right.k[1]);

					finished = true;
					//System.out.printf("스택에 노드가 존재하지 않음. 새로운 노드 생성\nroot.k[1] = %d\n왼쪽 = %d\n오른쪽 = %d\n", root.k[1], root.p[0].k[1], root.p[1].k[1]);
					//System.out.printf("left의 키 = %d, y의 키 = %d\n", left.k[1], right.k[1]);
				}
			}
		}while(!finished);
	}
	
	public static void inorder(Node root) {

		//System.out.printf("이 노드의 키의 개수 : %d\n", root.n);
		int i = 0;
		if(root.p[i] != null) {
			//System.out.printf("p[%d] 탐색\n", i);
			inorder(root.p[i]);
		}
		
		i++;
		
		while(i != root.m) {
			if(root.k[i] != 0) {
				System.out.printf("%d ", root.k[i]);
			}
			if(root.p[i] != null) {
				//System.out.printf("p[%d] 탐색\n", i);
				inorder(root.p[i]);
			}
			
			i++;
		}
	}	

	public static void main(String[] args) throws IOException {
		
		//입력할 배열 입력받기
		ArrayList<Integer> arr = new ArrayList<Integer>();
		BufferedReader br = new BufferedReader(new FileReader("C:\\Users\\hyojoon\\Desktop\\화일처리\\BTree\\insert.txt"));
		while(true) {			
			String line = br.readLine();
        	if(line == null)	break;        	
        	arr.add(Integer.parseInt(line));
        }
		
		System.out.println("\n\n----------m이 3일 때----------");
		Node tree3 = new Node(3);		
		for(int i = 0; i < arr.size(); i++) { 
			System.out.printf("\n(%d 삽입)\n", arr.get(i));
			insertBT(tree3, 3, arr.get(i));	
			inorder(tree3);
			System.out.println();
		}
		
		System.out.println("\n\n----------m이 4일 때----------");
		Node tree4 = new Node(4);		
		for(int i = 0; i < arr.size(); i++) { 
			System.out.printf("\n(%d 삽입)\n", arr.get(i));
			insertBT(tree4, 4, arr.get(i));	
			inorder(tree4);
			System.out.println();
		}
	}
}
