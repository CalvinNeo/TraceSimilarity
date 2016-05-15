package gui;

import java.awt.*;

import javax.swing.*;

public class TopLeftPanel extends JPanel {

	public TopLeftPanel() {
		initComponents();
	}

	public TopLeftPanel(LayoutManager layout) {
		super(layout);
		initComponents();
	}

	public TopLeftPanel(boolean isDoubleBuffered) {
		super(isDoubleBuffered);
		initComponents();
	}

	public TopLeftPanel(LayoutManager layout, boolean isDoubleBuffered) {
		super(layout, isDoubleBuffered);
		initComponents();
	}

	private JPanel leftUpperPanel, leftLowerPanel, leftMiddlePanel;

	private void initComponents() {
		createLeftPanel();
	}

	public void createLeftUpperPanel() {

		leftUpperPanel = new JPanel();
		leftUpperPanel.setLayout(new BoxLayout(leftUpperPanel, BoxLayout.Y_AXIS));

		JLabel sourceLabel = new JLabel("轨迹相似度计算");
		sourceLabel.setAlignmentY(Component.TOP_ALIGNMENT);
		sourceLabel.setBorder(BorderFactory.createEmptyBorder(5, 50, 10, 0));
		leftUpperPanel.add(sourceLabel);

		JComboBox<String> choice = new JComboBox<>(TraceManager.name);
		// choice.addItemListener(this);
		// choice.select(0);
		choice.setFont(new java.awt.Font("Dialog", 0, 11));
		choice.setName("choice");
		choice.setBackground(java.awt.Color.white);
		choice.setForeground(java.awt.Color.black);
		leftUpperPanel.add(choice);
		// leftUpperPanel.setAlignmentY(Component.TOP_ALIGNMENT);

	}

	public void createLeftLowerPanel() {

		JButton actionButton = new JButton("计算");
		JButton closeButton = new JButton("取消");
		leftLowerPanel = new JPanel();
		leftLowerPanel.setLayout(new BoxLayout(leftLowerPanel, BoxLayout.Y_AXIS));
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
		buttonPanel.add(Box.createHorizontalGlue());
		leftLowerPanel.add(Box.createVerticalStrut(10));
		buttonPanel.add(actionButton);
		buttonPanel.add(Box.createHorizontalStrut(30));
		buttonPanel.add(closeButton);
		buttonPanel.add(Box.createHorizontalStrut(40));
		leftLowerPanel.add(buttonPanel);
		leftLowerPanel.add(Box.createVerticalGlue());

	}

	public void createLeftMiddlePanel() {

		leftMiddlePanel = new JPanel();
		leftMiddlePanel.setLayout(new BoxLayout(leftMiddlePanel, BoxLayout.Y_AXIS));
		leftMiddlePanel.setBorder(BorderFactory.createEmptyBorder(10, 0, 0, 0));
		JTextArea textArea = new JTextArea();
		leftMiddlePanel.add(textArea);
		leftMiddlePanel.setVisible(false);

	}

	public void createLeftPanel() {

		createLeftUpperPanel();
		createLeftMiddlePanel();
		createLeftLowerPanel();

		this.setLayout(new GridBagLayout());
		this.setBorder(BorderFactory.createEmptyBorder(5, 20, 5, 20));

		GridBagConstraints c1 = new GridBagConstraints();
		c1.gridx = 0;
		c1.gridy = 0;
		c1.weightx = 1.0;
		c1.weighty = 0;
		c1.fill = GridBagConstraints.HORIZONTAL;
		this.add(leftUpperPanel, c1);

		GridBagConstraints c2 = new GridBagConstraints();
		c2.gridx = 0;
		c2.gridy = 1;
		c2.weightx = 1.0;
		c2.weighty = 100.0;
		c2.fill = GridBagConstraints.BOTH;
		this.add(leftMiddlePanel, c2);

		GridBagConstraints c3 = new GridBagConstraints();
		c3.gridx = 0;
		c3.gridy = 2;
		c3.weightx = 1.0;
		c3.weighty = 0;
		c3.fill = GridBagConstraints.HORIZONTAL;
		this.add(leftLowerPanel, c3);

	}

}
