package gui;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.*;

public class TopRightPanel extends JPanel implements ActionListener {

	public TopRightPanel() {
		initComponents();
	}

	public TopRightPanel(LayoutManager layout) {
		super(layout);
		initComponents();
	}

	public TopRightPanel(boolean isDoubleBuffered) {
		super(isDoubleBuffered);
		initComponents();
	}

	public TopRightPanel(LayoutManager layout, boolean isDoubleBuffered) {
		super(layout, isDoubleBuffered);
		initComponents();
	}

	private JPanel rightUpperPanel, rightLowerPanel;
	private ArrayList<JCheckBox> jcb;
	private JButton reverseButton, clearButton, allButton, actionButton;

	private void initComponents() {
		this.createRightPanel();
	}

	public void createRightUpperPanel() {

		rightUpperPanel = new JPanel();
		rightUpperPanel.setLayout(new BoxLayout(rightUpperPanel, BoxLayout.X_AXIS));

		jcb = new ArrayList<JCheckBox>();
		for (String string : TraceManager.name) {
			jcb.add(new JCheckBox(string));
		}
		JPanel listPanel = new JPanel();// 定义一个面板
		listPanel.setLayout(new GridLayout(TraceManager.n, 1));
		for (JCheckBox checkBox : jcb) {
			listPanel.add(checkBox);
		}
		JScrollPane sourceListScroller = new JScrollPane(listPanel);
		sourceListScroller.setPreferredSize(new Dimension(120, 200));
		sourceListScroller.setColumnHeaderView(new JLabel("选择要显示的轨迹"));
		sourceListScroller.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		sourceListScroller.setAlignmentY(Component.TOP_ALIGNMENT);
		rightUpperPanel.add(sourceListScroller);

	}

	public void createRightLowerPanel() {

		reverseButton = new JButton("反选");
		clearButton = new JButton("全不选");
		allButton = new JButton("全选");
		actionButton = new JButton("显示");
		rightLowerPanel = new JPanel();
		rightLowerPanel.setLayout(new BoxLayout(rightLowerPanel, BoxLayout.Y_AXIS));
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
		buttonPanel.add(Box.createHorizontalGlue());
		rightLowerPanel.add(Box.createVerticalStrut(20));
		buttonPanel.add(reverseButton);
		buttonPanel.add(Box.createHorizontalStrut(30));
		buttonPanel.add(clearButton);
		buttonPanel.add(Box.createHorizontalStrut(30));
		buttonPanel.add(allButton);
		buttonPanel.add(Box.createHorizontalStrut(30));
		buttonPanel.add(actionButton);
		buttonPanel.add(Box.createHorizontalStrut(30));
		rightLowerPanel.add(buttonPanel);
		reverseButton.addActionListener(this);
		clearButton.addActionListener(this);
		allButton.addActionListener(this);
		actionButton.addActionListener(this);

	}

	public void createRightPanel() {

		createRightUpperPanel();
		createRightLowerPanel();

		this.setLayout(new GridBagLayout());
		this.setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));

		GridBagConstraints c1 = new GridBagConstraints();
		c1.gridx = 0;
		c1.gridy = 0;
		c1.weightx = 1.0;
		c1.weighty = 1.0;
		c1.fill = GridBagConstraints.HORIZONTAL;
		this.add(rightUpperPanel, c1);

		GridBagConstraints c2 = new GridBagConstraints();
		c2.gridx = 0;
		c2.gridy = 1;
		c2.weightx = 1.0;
		c2.weighty = 0;
		c2.fill = GridBagConstraints.HORIZONTAL;
		this.add(rightLowerPanel, c2);

	}

	public void actionPerformed(ActionEvent e) {
		if (e.getID() == ActionEvent.ACTION_PERFORMED) {
			JButton tmp = (JButton) e.getSource();
			if (tmp == reverseButton) {
				for (JCheckBox jCheckBox : jcb) {
					jCheckBox.setSelected(!jCheckBox.isSelected());
				}
			} else if (tmp == clearButton) {
				for (JCheckBox jCheckBox : jcb) {
					jCheckBox.setSelected(false);
				}
			} else if (tmp == allButton) {
				for (JCheckBox jCheckBox : jcb) {
					jCheckBox.setSelected(true);
				}
			} else if (tmp == actionButton) {
				
			}
		}
	}

}
