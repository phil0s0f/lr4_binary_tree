using System.Windows;
using System.Windows.Controls;
using System.Windows.Shapes;

namespace btree
{
	public partial class MainWindow : Window
	{
		Btree root;
		Btree addTree(Btree root, int a, Btree ptr)
		{
			if (root == null) //если дерева нет
			{
				root = new Btree(a);
			}
			else if (a < root.X)
			{
				ptr = root;
				root.left = addTree(root.left, a, ptr);
			}
			else
			{
				ptr = root;
				root.right = addTree(root.right, a, ptr);
			}
			return root;
		}
		
		private void Add_Click(object sender, RoutedEventArgs e)
		{
			if (string.IsNullOrEmpty(NodeData.Text))
			{
				MessageBox.Show("Введите значение", "Напоминание");
				return;
			}
			else if (!int.TryParse(NodeData.Text, out int value))
			{
				MessageBox.Show($"Ожидается тип {typeof(int)}", "Ошибка");
				return;
			}
			else
			{
				int a = int.Parse(NodeData.Text);
				NodeData.Clear();
				Btree ptr = null;
				if (root == null)
					root = addTree(root, a, ptr);
				else
					addTree(root, a, ptr);
				TreeCanvas.Children.Clear();
				drawTree(root, 640, 0, 50, 50, 640, 0);
			}
		}
		Btree minim(Btree root)
		{
			if (root.left == null)
				return root;
			return minim(root.left);
		}
		Btree deleteTree(Btree root, int n)
		{
			if (root != null)
			{
				if (n < root.X) // если удаляемый эл. в L поддереве
					root.left = deleteTree(root.left, n);
				else if (n > root.X) // если в R 
					root.right = deleteTree(root.right, n);
				else if (root.left != null && root.right != null) // если это корень с 2мя потомками
				{
					root.X = minim(root.right).X; // заменяем мин. элементом из R поддерева
					root.right = deleteTree(root.right, root.X); // удаляем этот элемент из R поддерева
				}
				else // если 1 потомок
				{
					if (root.left != null)
						root = root.left;
					else if (root.right != null)
						root = root.right;
					else
						root = null;
				}
			}
			return root;
		}
		
		private void Delete_Click(object sender, RoutedEventArgs e)
        {
			if (string.IsNullOrEmpty(NodeData.Text))
			{
				MessageBox.Show("Введите значение", "Напоминание");
				return;
			}
			else if (!int.TryParse(NodeData.Text, out int value))
			{
				MessageBox.Show($"Ожидается тип {typeof(int)}", "Ошибка");
				return;
			}
			else
			{
				int y = int.Parse(NodeData.Text);
				NodeData.Clear();
				root = deleteTree(root, y);
				TreeCanvas.Children.Clear();
				drawTree(root, 640, 0, 50, 50, 640, 0);
			}
		}

		void drawTree(Btree node, double x, double y, double dx, double dy, double x1, double y1)
		{
			if (node == null)
				return;
			TextBox Text = new TextBox();
			Text.IsReadOnly = true;
			Text.FontSize = 20;
			Text.Text = node.X.ToString();
			Text.FontWeight = FontWeights.UltraBold;

			Line line = new Line()
			{
				X1 = x1,
				Y1 = y1,
				X2 = x,
				Y2 = y,
				Stroke = System.Windows.Media.Brushes.Black,
				StrokeThickness = 1
			};
			TreeCanvas.Children.Add(line);
			TreeCanvas.Children.Add(Text);
			Canvas.SetLeft(Text, x);
			Canvas.SetTop(Text, y);
			drawTree(node.left, x - 6*dx, y + 2*dy, dx / 2, dy, x, y);
			drawTree(node.right, x + 6*dx, y + 2*dy, dx / 2, dy, x, y);
		}
	}
    public class Btree
	{
		public Btree(int data)
		{
			X = data;
		}
		public int X { get; set; }
		public Btree left { get; set; }
		public Btree right { get; set; }
	};
}
