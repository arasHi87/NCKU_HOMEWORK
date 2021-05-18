package application;


import javafx.scene.control.Button;
import javafx.fxml.FXML;
import javafx.event.ActionEvent;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.scene.control.Label;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyCodeCombination;
import javafx.scene.input.KeyCombination;
import javafx.scene.input.KeyEvent;

import java.util.ArrayList;
import java.util.List;
import java.math.BigDecimal;
import java.math.RoundingMode;


public class SampleController {
	
	@FXML
	private Label history, input, output;

	@FXML
	private Button one, two, three, four, five, six, seven, eight, nine, zero,
					dot, add, sub, mul, div, all_clear, clear_entry, backspace;
	
    private List<Double> numbers=new ArrayList<Double>();
    private List<String> operators=new ArrayList<String>();
    private Boolean AlreadyClearEntry=false;
	
	public void initialize(URL location, ResourceBundle resources) {
    }
	
	private String getButtonValue(ActionEvent event){
        Button button = (Button)event.getSource();
        return button.getText();
    }

	private boolean isBlank(String text){
        if(text!=null && text!="" && text.length()>0)
            return false;
        return true;
    }
	
	public void BindKey(KeyEvent event) {
		KeyCode code=event.getCode();
		KeyCombination AddCombo = new KeyCodeCombination(KeyCode.EQUALS, KeyCombination.SHIFT_ANY);
		KeyCombination MulCombo = new KeyCodeCombination(KeyCode.DIGIT8, KeyCombination.SHIFT_ANY);
		
		if (code.equals(KeyCode.SUBTRACT) || AddCombo.match(event)) add.fire();
		else if (code.equals(KeyCode.MULTIPLY) || MulCombo.match(event)) mul.fire();
		else if (code.equals(KeyCode.DIGIT1) || code.equals(KeyCode.NUMPAD1)) one.fire();
		else if (code.equals(KeyCode.DIGIT2) || code.equals(KeyCode.NUMPAD2)) two.fire();
		else if (code.equals(KeyCode.DIGIT3) || code.equals(KeyCode.NUMPAD3)) three.fire();
		else if (code.equals(KeyCode.DIGIT4) || code.equals(KeyCode.NUMPAD4)) four.fire();
		else if (code.equals(KeyCode.DIGIT5) || code.equals(KeyCode.NUMPAD5)) five.fire();
		else if (code.equals(KeyCode.DIGIT6) || code.equals(KeyCode.NUMPAD6)) six.fire();
		else if (code.equals(KeyCode.DIGIT7) || code.equals(KeyCode.NUMPAD7)) seven.fire();
		else if (code.equals(KeyCode.DIGIT8) || code.equals(KeyCode.NUMPAD8)) eight.fire();
		else if (code.equals(KeyCode.DIGIT9) || code.equals(KeyCode.NUMPAD9)) nine.fire();
		else if (code.equals(KeyCode.DIGIT0) || code.equals(KeyCode.NUMPAD0)) zero.fire();
		else if (code.equals(KeyCode.PERIOD)) dot.fire();
		else if (code.equals(KeyCode.MINUS)) sub.fire();
		else if (code.equals(KeyCode.SLASH)) div.fire();
		else if (code.equals(KeyCode.A)) all_clear.fire();
		else if (code.equals(KeyCode.C)) clear_entry.fire();
		else if (code.equals(KeyCode.BACK_SPACE)) backspace.fire();
	}
	
	public void pressNumber(ActionEvent event) {
		System.out.println(event);
		// clear CE flag first
		AlreadyClearEntry=false;
		
		String number = getButtonValue(event);
		String result = input.getText();
		
		if (".".equals(number.trim())) {
			if (result.contains(".") || isBlank(result))
				return;
			else {
				input.setText(result + '.');
				return;
			}
		}
		input.setText(input.getText() + number);
	}
	
	public void pressOperator(ActionEvent event) {
		String result = input.getText();
		if (isBlank(result))
			return;
		input.setText(input.getText() + getButtonValue(event));	
	}
	
	public void pressEqual(ActionEvent event) {
		history.setText(input.getText());
		// Split equation
		String equation = input.getText(), tmp="";
		for (char ch:equation.toCharArray()) {
			if (Character.isDigit(ch)) tmp+=ch;
			else {
				numbers.add(Double.parseDouble(tmp));
				operators.add(String.valueOf(ch));
				tmp="";
			}
		} numbers.add(Double.parseDouble(tmp));
		
		// calculate
		// deal with multiple and diversion first
		for (int i=0;i<operators.size();i++) {
			String ch=operators.get(i);
			if (ch.equals("*") || ch.equals("/")) {
				System.out.println(ch);
				operators.remove(i); // remove operator from OP list
				Double left = numbers.remove(i); // get operator left side number
				Double right = numbers.remove(i); // get operator right side number
				
				// check if right is 0 when divide
				if (ch.equals("/") && right==0.0) {
					input.setText("");
					output.setText("Error");
					return;
				}
				
				if (ch.equals("*")) numbers.add(i, left*right);
				else numbers.add(i, left/right);
				
				// avoid escape next operator
				i--;
			}
		}
		
		// finish add and subtract operators
		while (!operators.isEmpty()) {
			String ch=operators.remove(0);
			Double left = numbers.remove(0); // get operator left side number
			Double right = numbers.remove(0); // get operator right side number
			
			if (ch.equals("+")) numbers.add(0, left+right);
			else numbers.add(0, left-right);
		}
		
		output.setText((new BigDecimal(numbers.remove(0)).setScale(1, RoundingMode.HALF_UP)).toString());
		input.setText("");
	}
	
	public void pressAllClear(ActionEvent event) {
		history.setText("");
		input.setText("");
		output.setText("");
	}
	
	public void pressClearEntry(ActionEvent event) {
		if (!AlreadyClearEntry) {
			StringBuilder str=new StringBuilder(input.getText());
			for (int i=str.length()-1;i>=0;i--) {
				if (!Character.isDigit(str.charAt(i))) break;
				str.deleteCharAt(i);
			}
			input.setText(str.toString());
		}
	}
	
	public void pressBackspace(ActionEvent event) {
		if (!isBlank(input.getText())) {
			String str=input.getText();
			input.setText(str.substring(0, str.length()-1));
		}
	}
}
