package gui;

import java.awt.*;

import javax.swing.*;

//import net.CInterface;

public class BigFrame extends JFrame {
	public BigFrame() throws HeadlessException {
		initComponents();
	}

	public BigFrame(GraphicsConfiguration gc) {
		super(gc);
		initComponents();
	}

	public BigFrame(String title) throws HeadlessException {
		super(title);
		initComponents();
	}

	public BigFrame(String title, GraphicsConfiguration gc) {
		super(title, gc);
		initComponents();
	}

	private JPanel bigPanel, topPanel, bottomPanel;

	public void createTopPanel() {

		TopLeftPanel leftPanel = new TopLeftPanel();
		TopRightPanel rightPanel = new TopRightPanel();
		topPanel = new JPanel(new GridBagLayout());

		GridBagConstraints c1 = new GridBagConstraints();
		c1.gridx = 0;
		c1.gridy = 0;
		c1.weightx = 1.0;
		c1.weighty = 1.0;
		c1.fill = GridBagConstraints.HORIZONTAL;
		topPanel.add(leftPanel, c1);

		GridBagConstraints c2 = new GridBagConstraints();
		c2.gridx = 1;
		c2.gridy = 0;
		c2.weightx = 1.0;
		c2.weighty = 1.0;
		c2.fill = GridBagConstraints.HORIZONTAL;
		topPanel.add(rightPanel, c2);

	}

	public void createBottomPanel() {
		bottomPanel = new JPanel();
		bottomPanel.setBackground(Color.blue);

	}

	public void createBigPanel() {

		createTopPanel();
		createBottomPanel();
		bigPanel = new JPanel(new GridBagLayout());

		GridBagConstraints c1 = new GridBagConstraints();
		c1.gridx = 0;
		c1.gridy = 0;
		c1.weightx = 1.0;
		c1.weighty = 0.5;
		c1.fill = GridBagConstraints.BOTH;
		bigPanel.add(topPanel, c1);

		GridBagConstraints c2 = new GridBagConstraints();
		c2.gridx = 0;
		c2.gridy = 1;
		// c2.gridheight = 3;
		c2.weightx = 1.0;
		c2.weighty = 10.0;
		c2.fill = GridBagConstraints.BOTH;
		bigPanel.add(bottomPanel, c2);

	}

	private void initComponents() {
		createBigPanel();
		this.setContentPane(bigPanel);
	}

	public static void main(String[] args) {
		BigFrame frame = new BigFrame("以经纬度和时间定义的不同轨迹的相似度计算");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		double width = Toolkit.getDefaultToolkit().getScreenSize().getWidth();
		double height = Toolkit.getDefaultToolkit().getScreenSize().getHeight();
		frame.setSize(800, 600);
		frame.setLocation((int) (width - frame.getWidth()) / 2 - 50, (int) (height - frame.getHeight()) / 2);
		frame.setVisible(true);
//		CInterface.socketmain();
	}
}
