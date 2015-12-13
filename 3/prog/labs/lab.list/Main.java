import java.util.*;

class Node<T> {
	public T value;
	public Node<T> next = null;
	public Node<T> prev = null;
	public Node(T value, Node<T> prev, Node<T> next) {
		this.value = value;
		this.prev = prev;
		this.next = next;
	}
}

class CustomList<T> extends AbstractSequentialList<T> {
	
	private Node<T> begin = null;
	private int size = 0;
	
	public CustomList(T[] list) {
		for (T v : list) add(v);
	}
	public String toString() {
		String[] a = new String[size()];
		for (int i = 0; i < size(); ++i) {
			a[i] = this.get(i).toString();
		}
		return "[" + String.join(", ", a) + "]";
	}
	@Override
	public CustomListIterator listIterator(int id) {
		return new CustomListIterator(id);
	}
	@Override
	public int size() {
		return this.size;
	}

	class CustomListIterator implements ListIterator<T> {
		private Node<T> next = null;
		private Node<T> prev = null;
		private Node<T> last = null;
		private int index = 0;
				
		public CustomListIterator(int i) {
			if (i < 0 || i > size()) {
				throw new IndexOutOfBoundsException();
			}
			next = begin;
			while (i-- > 0 && hasNext()) next();
		}
		public void fit(Node<T> prev, Node<T> next) {
			this.prev = prev;
			this.next = next;
		}
		@Override
		public void add(T v) {
			Node<T> e = new Node<T>(v, prev, next);
			if (begin == null) {
				begin = e;
			}
			if (next != null) {
				next.prev = e;
			}
			if (prev != null) {
				prev.next = e;
			}
			fit(e, next);
			++size;
			++index;
		}
		@Override
		public void set(T v) {
			if (last == null) {
				throw new IllegalStateException();
			}
			last.value = v;
		}
		@Override
		public void remove() {
			if (last == null) {
				throw new IllegalStateException();
			}
			if (next == last) {
				next = last.next;
			}
			if (prev == last) {
				prev = last.prev;
				--index;
			}
			if (last.prev != null) {
				last.prev.next = last.next;
			}
			if (last.next != null) {
				last.next.prev = last.prev;
			}
			last = null;
			--size;
		}
		@Override
		public int previousIndex() {
			return index - 1;
		}
		@Override
		public int nextIndex() {
			return index + 1;
		}
		@Override
		public T next() {
			if (!this.hasNext()) {
				throw new NoSuchElementException();
			}
			fit(next, next.next);
			last = prev;
			++index;
			return prev.value;
		}
		@Override
		public T previous() {
			if (!this.hasPrevious()) {
				throw new NoSuchElementException();
			}
			fit(prev.prev, prev);
			last = next;
			--index;
			return next.value;
		}
		@Override
		public boolean hasPrevious() {
			return prev != null;
		}
		@Override
		public boolean hasNext() {
			return next != null;
		}
	}
}

public class Main {
	public static void main(String[] args) {
		CustomList<Integer> list = new CustomList<Integer>(new Integer[]{1,2,3,4});
		System.out.println(list);
		list.add(5);
		System.out.println(list);
		ListIterator<Integer> it = list.listIterator(2);
		it.add(9);
		System.out.println(list);
		it.next();
		it.set(99);
		System.out.println(list);
		it.remove();
		System.out.println(list);
		it.next();
		it.remove();
		System.out.println(list);
		it.remove();
	}
}